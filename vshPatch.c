// Thanks Dots and Princess for helping me haha
// Fios2 memes :D


#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <vitasdkkern.h>
#include <psp2kern/kernel/proc_event.h>
#include <taihen.h>

#define printf ksceDebugPrintf


typedef struct mount_point_overlay{
  uint8_t type;
  uint8_t order;
  uint16_t dst_len;
  uint16_t src_len;
  uint32_t PID;
  uint32_t mountId;
  char dst[292];
  char src[292];
} mount_point_overlay;


static mount_point_overlay overlay;
static int overlay_out;

int create_proc(SceUID pid, SceProcEventInvokeParam2 *a2, int a3)
{
	overlay.type = 1;
	overlay.order = 0xFF;
	overlay.dst_len = 5;
	overlay.src_len = 14;
	overlay.PID = pid;
	overlay.mountId = 0;
	strncpy(overlay.dst, "vs0:", 5);
	strncpy(overlay.src,"ux0:/vshPatch", 14);
	overlay_out = 0;
	
	int ret = ksceFiosKernelOverlayAddForProcess(pid, &overlay, &overlay_out);
	printf("ret = 0x%x overlay_out = 0x%x pid=%x\n", ret, overlay_out, pid);
	
	return 0;
}

void _start() __attribute__ ((weak, alias ("module_start")));
int module_start(SceSize argc, const void *args)
{
	SceProcEventHandler handler;
	memset(&handler, 0, sizeof(handler));
	handler.size = sizeof(handler);
	handler.create = create_proc;

	int ret = ksceKernelRegisterProcEventHandler("SceRemapVs0ToUx0Vs0Patch", &handler, 0);
	
	printf("ksceKernelRegisterProcEventHandler ret = 0x%x\n", ret);
	return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args)
{ 	
	return SCE_KERNEL_STOP_SUCCESS;
}
