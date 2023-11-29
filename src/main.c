/*
 * Copyright (c) 2021 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/zephyr.h>
#include <zephyr/audio/dmic.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(dmic_sample);

#define MAX_SAMPLE_RATE  16000
#define SAMPLE_BIT_WIDTH 16
#define BYTES_PER_SAMPLE sizeof(int16_t)
/* Milliseconds to wait for a block to be read. */
#define READ_TIMEOUT     1000

/* Size of a block for 100 ms of audio data. */
#define BLOCK_SIZE(_sample_rate, _number_of_channels) \
	(BYTES_PER_SAMPLE * (_sample_rate / 10) * _number_of_channels)

/* Driver will allocate blocks from this slab to receive audio data into them.
 * Application, after getting a given block from the driver and processing its
 * data, needs to free that block.
 */
#define MAX_BLOCK_SIZE   BLOCK_SIZE(MAX_SAMPLE_RATE, 2)
#define BLOCK_COUNT      4
K_MEM_SLAB_DEFINE_STATIC(mem_slab, MAX_BLOCK_SIZE, BLOCK_COUNT, 4);

int counter = 0;

float audio[32000];

// define wrapper
static int wrapper_add_data(const void *data, size_t data_size)
{
	counter++;
	printk("wrapper_add_data\n");
	printk("data_size: %d\n", data_size);
	printk("counter: %d\n", counter);

	// print the data
	for (int i = 0; i < data_size; i++) {
		printk("%d ", ((uint8_t *)data)[i]);
	}

	return 0;
}

static int do_pdm_transfer(const struct device *dmic_dev,
			   struct dmic_cfg *cfg,
			   size_t block_count)
{
	int ret;

	LOG_INF("PCM output rate: %u, channels: %u",
		cfg->streams[0].pcm_rate, cfg->channel.req_num_chan);

	ret = dmic_configure(dmic_dev, cfg);
	if (ret < 0) {
		LOG_ERR("Failed to configure the driver: %d", ret);
		return ret;
	}

	ret = dmic_trigger(dmic_dev, DMIC_TRIGGER_START);
	if (ret < 0) {
		LOG_ERR("START trigger failed: %d", ret);
		return ret;
	}

	// for (int i = 0; i < block_count; ++i) {
	for (int i = 0; i < 21; ++i) {
		void *buffer;
		uint32_t size;
		int ret;

		ret = dmic_read(dmic_dev, 0, &buffer, &size, READ_TIMEOUT);
		if (ret < 0) {
			LOG_ERR("%d - read failed: %d", i, ret);
			return ret;
		}

		LOG_INF("%d - got buffer %p of %u bytes", i, buffer, size);

		if(i!=0){
			printk("i: %d\n", i);
			int16_t tempInt;
			float tempFloat;
			for(int j=0; j<1600; j++){
				memcpy(&tempInt, buffer + 2*j, 2);
				tempFloat = (float)tempInt;
				audio[(i-1)*1600+j] = tempFloat;
			}
		}

		// print buffer
		// for (int i = 0; i < size; i++) {
		// 	printk("%d ", ((uint8_t *)buffer)[i]);
		// }
		// printk("\n");

		k_mem_slab_free(&mem_slab, &buffer);

	}

	ret = wrapper_add_data(&audio, sizeof(audio));
	if (ret) {
		LOG_INF("Cannot provide input data (err: %d)\n", ret);
		LOG_INF("Increase CONFIG_EI_WRAPPER_DATA_BUF_SIZE\n");
	}

	ret = dmic_trigger(dmic_dev, DMIC_TRIGGER_STOP);
	if (ret < 0) {
		LOG_ERR("STOP trigger failed: %d", ret);
		return ret;
	}

	return ret;
}

void main(void)
{
	// while(1){
	printk("DMIC sample started\n");
	// k_sleep(K_MSEC(1000));
	// }
	const struct device *dmic_dev = DEVICE_DT_GET(DT_NODELABEL(dmic_dev));
	int ret;

	LOG_INF("DMIC sample");

	if (!device_is_ready(dmic_dev)) {
		LOG_ERR("%s is not ready", dmic_dev->name);
		return;
	}

	printk("DMIC device: %s\n", dmic_dev->name);

	struct pcm_stream_cfg stream = {
		.pcm_width = SAMPLE_BIT_WIDTH,
		.mem_slab  = &mem_slab,
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
	cfg.streams[0].pcm_rate = MAX_SAMPLE_RATE;
	cfg.streams[0].block_size =
		BLOCK_SIZE(cfg.streams[0].pcm_rate, cfg.channel.req_num_chan);

	ret = do_pdm_transfer(dmic_dev, &cfg, 2 * BLOCK_COUNT);
	// ret = do_pdm_transfer(dmic_dev, &cfg, BLOCK_COUNT);
	if (ret < 0) {
		return;
	}

	// printk("DMIC sample finished\n");
	LOG_INF("DMIC sample finished\n");

	// print the data
	// for (int i = 0; i < 2 * BLOCK_COUNT; i++) {
	// 	printk("%d ", ((uint8_t *)mem_slab)[i]);
	// }
	// printk("\n");

	// cfg.channel.req_num_chan = 2;for (int i = 0; i < 2 * BLOCK_COUNT; i++) {
	// 	printk("%d ", ((uint8_t *)mem_slab)[i]);
	// }
	// printk("\n");
	// cfg.channel.req_chan_map_lo =
	// 	dmic_build_channel_map(0, 0, PDM_CHAN_LEFT) |
	// 	dmic_build_channel_map(1, 0, PDM_CHAN_RIGHT);
	// cfg.streams[0].pcm_rate = MAX_SAMPLE_RATE;
	// cfg.streams[0].block_size =
	// 	BLOCK_SIZE(cfg.streams[0].pcm_rate, cfg.channel.req_num_chan);

	// ret = do_pdm_transfer(dmic_dev, &cfg, 2 * BLOCK_COUNT);

	// printk("DMIC sample finished\n");

	// if (ret < 0) {
	// 	return;
	// }

	LOG_INF("Exiting");
}
