/*
 * Copyright (c) 2020 STMicroelectronics
 *
 * SPDX-License-Identifier: Apache-2.0
 * 
 * @ Arnav Kharbhanda
 * @ VinayYadav
 */

#include <string.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/audio/dmic.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(dmic_sample);

/* uncomment if you want PCM output in ascii */
//#define PCM_OUTPUT_IN_ASCII		1

#define AUDIO_FREQ		16000
#define CHAN_SIZE		16
#define PCM_BLK_SIZE_MS		((AUDIO_FREQ/1000) * sizeof(int16_t))

#define READ_TIMEOUT_MS		2000

// 1 seconds
#define NUM_MS		1000

// added some extra blocks: 2 for safety
K_MEM_SLAB_DEFINE(rx_mem_slab, PCM_BLK_SIZE_MS, NUM_MS + 2, 1);

void *rx_block[NUM_MS];
size_t rx_size = PCM_BLK_SIZE_MS;

int main(void)
{
	int i;
	uint32_t ms;
	int ret;

	LOG_INF("DMIC sample started\n");

	//const struct device *const mic_dev = DEVICE_DT_GET_ONE(st_mpxxdtyy);
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
			LOG_INF("%d microphone audio read success %p %u.\n", ms, rx_block[ms], rx_size);
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

	/* print PCM stream */
#ifdef PCM_OUTPUT_IN_ASCII	
	printk("-- start\n");
	int j;

	for (i = 0; i < NUM_MS; i++) {
		uint16_t *pcm_out = rx_block[i];

		for (j = 0; j < rx_size/2; j++) {
			printk("0x%04x, \n", pcm_out[j]);
			k_sleep(K_MSEC(1));			
		}
		printk("-- mid\n");
	}
	printk("-- end\n");
#endif
	return 0;
}
