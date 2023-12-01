/*
 * Copyright (c) 2019 Tavish Naruka <tavishnaruka@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* Sample which uses the filesystem API and SDHC driver */

#include <zephyr/zephyr.h>
#include <zephyr/device.h>
#include <zephyr/storage/disk_access.h>
#include <zephyr/logging/log.h>
#include <zephyr/fs/fs.h>
#include <ff.h>

// For audio
#include <string.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/audio/dmic.h>

LOG_MODULE_REGISTER(main);

// Audio params -----------------------------------
#define AUDIO_FREQ		16000
#define CHAN_SIZE		16
#define PCM_BLK_SIZE_MS		((AUDIO_FREQ/1000) * sizeof(int16_t))

#define READ_TIMEOUT_MS		2000

// 1 seconds
#define NUM_MS		5000

// added some extra blocks: 2 for safety
K_MEM_SLAB_DEFINE(rx_mem_slab, PCM_BLK_SIZE_MS, NUM_MS + 2, 1);

void *rx_block[NUM_MS];
size_t rx_size = PCM_BLK_SIZE_MS;


// SD params -----------------------------------
static int lsdir(const char *path);

static FATFS fat_fs;
/* mounting info */
static struct fs_mount_t mp = {
	.type = FS_FATFS,
	.fs_data = &fat_fs,
};

/*
*  Note the fatfs library is able to mount only strings inside _VOLUME_STRS
*  in ffconf.h
*/
static const char *disk_mount_pt = "/SD:";

void main(void)
{
	// Audio ------------------
	int i;
	uint32_t ms;
	int ret;

	const struct device *const mic_dev = DEVICE_DT_GET(DT_NODELABEL(dmic_dev));

	if (!device_is_ready(mic_dev)) {
		LOG_ERR("%s: device not ready.\n", mic_dev->name);
		return 0;
	}

	struct pcm_stream_cfg stream = {
		.pcm_width = CHAN_SIZE,
		.mem_slab  = &rx_mem_slab,
	};

	struct dmic_cfg cfg = {
		.io = {
			/* These fields can be used to limit the PDM clock
			 * configurations that the driver is allowed to use
			 * to those supported by the microphone.
			 */
			.min_pdm_clk_freq = 1000000,
			.max_pdm_clk_freq = 3500000,
			.min_pdm_clk_dc   = 40,
			.max_pdm_clk_dc   = 60,
		},
		.streams = &stream,
		.channel = {
			.req_num_streams = 1,
		},
	};

	cfg.channel.req_num_chan = 1;
	cfg.channel.req_chan_map_lo =
		dmic_build_channel_map(0, 0, PDM_CHAN_LEFT);
	cfg.streams[0].pcm_rate = AUDIO_FREQ;
	cfg.streams[0].block_size = PCM_BLK_SIZE_MS;

	ret = dmic_configure(mic_dev, &cfg);
	if (ret < 0) {
		LOG_ERR("microphone configuration error\n");
		return 0;
	}
	else{
		LOG_INF("microphone configuration success\n");
	}
	// ------------------

	/* raw disk i/o */
	do {
		static const char *disk_pdrv = "SD";
		uint64_t memory_size_mb;
		uint32_t block_count;
		uint32_t block_size;

		if (disk_access_init(disk_pdrv) != 0) {
			LOG_ERR("Storage init ERROR!");
			break;
		}

		if (disk_access_ioctl(disk_pdrv,
				DISK_IOCTL_GET_SECTOR_COUNT, &block_count)) {
			LOG_ERR("Unable to get sector count");
			break;
		}
		LOG_INF("Block count %u", block_count);

		if (disk_access_ioctl(disk_pdrv,
				DISK_IOCTL_GET_SECTOR_SIZE, &block_size)) {
			LOG_ERR("Unable to get sector size");
			break;
		}
		printk("Sector size %u\n", block_size);

		memory_size_mb = (uint64_t)block_count * block_size;
		printk("Memory Size(MB) %u\n", (uint32_t)(memory_size_mb >> 20));
	} while (0);

	mp.mnt_point = disk_mount_pt;

	int res = fs_mount(&mp);

	if (res == FR_OK) {
		printk("Disk mounted.\n");
		lsdir(disk_mount_pt);
	} else {
		printk("Error mounting disk.\n");
	}

	// Audio get data ------------------
	ret = dmic_trigger(mic_dev, DMIC_TRIGGER_START);
	if (ret < 0) {
		LOG_ERR("microphone start trigger error\n");
		return 0;
	}
	else{
		LOG_INF("microphone start trigger success\n");
	}

	/* Acquire microphone audio */
	for (ms = 0; ms < NUM_MS; ms++) {
		ret = dmic_read(mic_dev, 0, &rx_block[ms], &rx_size, READ_TIMEOUT_MS);
		if (ret < 0) {
			LOG_ERR("%d microphone audio read error %p %u.\n", ms, rx_block[ms], rx_size);
			return 0;
		}
		else{
			LOG_INF("%d mic success %p %u.\n", ms, rx_block[ms], rx_size);
		}

	}
	
	ret = dmic_trigger(mic_dev, DMIC_TRIGGER_STOP);
	if (ret < 0) {
		LOG_ERR("microphone stop trigger error\n");
		return 0;
	}
	else{
		LOG_INF("microphone stop trigger success\n");
	}
	// ------------------------------------------

	// sleep for 2 second
	k_sleep(K_MSEC(2000));

	printk("Attempting to write to file...\n");
	{
		char filename[30];	
		int write_index = 5555;

		struct fs_file_t filep;
		size_t bytes_written;

		fs_file_t_init(&filep);

		sprintf(&filename, "/SD:/%d_01.txt", write_index);
		fs_unlink(filename);

		res = fs_open(&filep, filename, FS_O_CREATE | FS_O_WRITE | FS_O_APPEND);
		if (res) {
			printk("Error opening file %s [%d]\n", filename, res);
			return;
		}
		else
		{
			printk("File %s opened successfully\n", filename);
		}

		// write in chunks of 50ms
		for (i = 0; i < NUM_MS/50; i++) {
			res = fs_write(&filep, rx_block[i*50], rx_size*50);
			if (res < 0) {
				printk("Error writing file [%d]\n", res);
			} else {
				printk("%d bytes written to file\n", res);
			}
		}

		res = fs_close(&filep);
		if (res < 0) {
			printk("Error closing file [%d]\n", res);
		}
	}

	// unmount the disk
	// fs_unmount(&mp);

	while (1) {
		k_sleep(K_MSEC(1000));
	}
}

static int lsdir(const char *path)
{
	int res;
	struct fs_dir_t dirp;
	static struct fs_dirent entry;

	fs_dir_t_init(&dirp);

	/* Verify fs_opendir() */
	res = fs_opendir(&dirp, path);
	if (res) {
		printk("Error opening dir %s [%d]\n", path, res);
		return res;
	}

	printk("\nListing dir %s ...\n", path);
	for (;;) {
		/* Verify fs_readdir() */
		res = fs_readdir(&dirp, &entry);

		/* entry.name[0] == 0 means end-of-dir */
		if (res || entry.name[0] == 0) {
			break;
		}

		if (entry.type == FS_DIR_ENTRY_DIR) {
			printk("[DIR ] %s\n", entry.name);
		} else {
			printk("[FILE] %s (size = %zu)\n",
				entry.name, entry.size);
		}
	}

	/* Verify fs_closedir() */
	fs_closedir(&dirp);

	return res;
}
