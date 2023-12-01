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

LOG_MODULE_REGISTER(main);

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

	printk("Attempting to write to file...\n");
	{
		static const char *hello_str = "Hello World!\n";
		// const char *file_path = "/SD:hello.txt";
		char filename[30];	
		int write_index = 3;

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

		uint8_t arr[10] = {1,2,3,4,5,6,7,8,9,10};

		// res = fs_write(&filep, hello_str, strlen(hello_str));
		res = fs_write(&filep, &arr, sizeof(arr));
		if (res < 0) {
			printk("Error writing file [%d]\n", res);
		} else {
			printk("%d bytes written to file\n", res);
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
