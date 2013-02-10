#include "lsp.h"
// #include "lspmessage.pb-c.h"

double epoch_lth = _EPOCH_LTH;
int epoch_cnt = _EPOCH_CNT;
double drop_rate = _DROP_RATE;

/*
 *
 *
 *				LSP RELATED FUNCTIONS
 *
 *
 */

void lsp_set_epoch_lth(double lth){epoch_lth = lth;}
void lsp_set_epoch_cnt(int cnt){epoch_cnt = cnt;}
void lsp_set_drop_rate(double rate){drop_rate = rate;}

/** LSP Methods */

/**
 * Code for execution as the listener thread
 */
void* listener_run(void* arg)
{
	struct ListenerData* params = (struct ListenerData *) arg;
	printf("Running Listener Thread...\n");
	params->lsp_instance->runListener();
}




