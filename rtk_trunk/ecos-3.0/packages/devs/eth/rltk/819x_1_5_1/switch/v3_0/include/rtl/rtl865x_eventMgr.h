/*
* Copyright c                  Realtek Semiconductor Corporation, 2008  
* All rights reserved.
* 
* Abstract : 
* Author : hyking (hyking_liu@realsil.com.cn) 
*/

#ifndef RTL865X_EVENT_MANAGEMENT_H
#define RTL865X_EVENT_MANAGEMENT_H

//#include <netinet/fastpath/rtl_queue.h>
#include <rtl/rtl_queue.h>

#define GFP_KERNEL		1
#define GFP_ATOMIC		1

#define TBL_MEM_ALLOC(tbl, type, size)   \
		{ \
		(tbl) = (type *)kmalloc((size) * sizeof(type),GFP_ATOMIC);\
				if(!(tbl)){\
						diag_printf("MEM alloc failed at line %d\n", __LINE__);\
						while(1);\
						return FAILED;\
				}\
		}
#if 1

#ifndef uint32
#define uint32 unsigned int
#endif
#ifndef int32
#define int32  int
#endif
#ifndef uint8
#define uint8 unsigned char
#endif
#ifndef int8
#define int8  char		
#endif
#ifndef uint16
#define uint16 unsigned short
#endif
#ifndef int16
#define int16 short			
#endif

#endif






#define DEFAULT_EVENT_LIST_CNT 	4
#define DEFAULT_EVENT_CNT			100

#define MAX_EVENT_LIST_CNT		20
#define MAX_EVENT_CNT			200


#define DEFAULT_COMMON_EVENT_LIST_ID		0x10000000
#define DEFAULT_LAYER2_EVENT_LIST_ID		0x20000000
#define DEFAULT_LAYER3_EVENT_LIST_ID		0x30000000
#define DEFAULT_LAYER4_EVENT_LIST_ID		0x40000000

#define RTL865X_EVENT_PROC_DIR "reasilEvent"

/*common layer event definition, common event range 0x10000000~0x1FFFFFFF*/
#define MIN_COMM_EVENT_ID 			0x10000000
#define MAX_COMM_EVENT_ID 		0x1FFFFFFF

#define EVENT_ADD_VLAN				0x10000001
#define EVENT_DEL_VLAN				0x10000002
#define EVENT_CHANGE_VLANFID		0x10000003
#define EVENT_ADD_NETIF			0x10000004
#define EVENT_DEL_NETIF			0x10000005
#define EVENT_ADD_ACL				0x10000006
#define EVENT_DEL_ACL				0x10000007

/*layer2 event definition, layer 2 event range 0x20000000~0x2FFFFFFF*/
#define MIN_LAYER2_EVENT_ID 		0x20000000
#define MAX_LAYER2_EVENT_ID 		0x2FFFFFFF

#define EVENT_ADD_FDB				0x20000001
#define EVENT_DEL_FDB				0x20000002
#define EVENT_ADD_AUTHED_FDB		0x20000004
#define EVENT_DEL_AUTHED_FDB		0x20000008

#define EVENT_CHANGE_QOSRULE		0x20001001
#define EVENT_FLUSH_QOSRULE		0x20001002


/*layer3 event definition, layer3 event range 0x30000000~0x3FFFFFFF*/
#define MIN_LAYER3_EVENT_ID 		0x30000000
#define MAX_LAYER3_EVENT_ID 		0x3FFFFFFF

#define EVENT_ADD_ROUTE			0x30000001
#define EVENT_DEL_ROUTE				0x30000001
#define EVENT_ADD_NEXTHOP			0x30000003
#define EVENT_DEL_NEXTHOP			0x30000004
#define EVENT_ADD_IP				0x30000005
#define EVENT_DEL_IP					0x30000006
#define EVENT_ADD_ARP				0x30000007
#define EVENT_DEL_ARP				0x30000008
#define EVENT_ADD_PPP				0x30000009
#define EVENT_DEL_PPP				0x30000010

/*macro for ip multicast usage*/
#define EVENT_UPDATE_MCAST		0x30000011
#define EVENT_ADD_MCAST			0x30000012
#define EVENT_DEL_MCAST			0x30000013
#define EVENT_ADD_GROUP			0x30000014
#define EVENT_DEL_GROUP			0x30000015
#define EVENT_ADD_MEMBER			0x30000016
#define EVENT_DEL_MEMBER			0x30000017
#define EVENT_ADD_SOURCE			0x30000018
#define EVENT_DEL_SOURCE			0x30000019
#if defined(CONFIG_RTL_8197F) && defined(CONFIG_RTL_MLD_SNOOPING) && defined(CONFIG_RTL_HARDWARE_MULTICAST)
#define EVENT_UPDATE_MCAST6		0x30000020
#endif

/*layer4 event definition, layer4 event range 0x40000000~0x4FFFFFFF*/
#define MIN_LAYER4_EVENT_ID 		0x40000000
#define MAX_LAYER4_EVENT_ID 		0x4FFFFFFF

#define EVENT_ADD_NAPT				0x40000001
#define EVENT_DELETE_NAPT			0x40000002

#define MAX_SYSTEM_EVENT_ID		0x4FFFFFFF

#define HIGHEST_EVENT_PRIORITY		1
#define LOWEST_EVENT_PRIORITY		65535

/*callback function return vlue definition*/
#define	EVENT_CONTINUE_EXECUTE	SUCCESS
#define	EVENT_STOP_EXECUTE		FAILED
#define	EVENT_RE_EXECUTE			(FAILED-1)


#ifdef __KERNEL__
	#define rtl865x_debug_printf	printk
#else
	#define rtl865x_debug_printf	printf
#endif

/*data structure definition*/
typedef struct rtl865x_eventMgr_param_s
{
	uint32 eventListCnt;
	uint32 eventCnt;
}rtl865x_eventMgr_param_t;

typedef struct rtl865x_event_Param_s
{
	int32 eventLayerId;	
	int32 eventId;
	int32 eventPriority;
	int32 (*event_action_fn)(void *param);
}rtl865x_event_Param_t;


typedef struct action_param_s
{
	void *org;	/*old information*/
	void *now;	/*new information*/
	void *flag;
}action_param_t;


typedef struct rtl865x_event_s
{
	int32 eventId;
	int32 eventPriority; /*priority: less value indicate higher priority*/	
	int32 (*event_action_fn)(void *param);	
	CTAILQ_ENTRY(rtl865x_event_s) next;
}rtl865x_event_t;


typedef CTAILQ_HEAD(_event_head_s, rtl865x_event_s) rtl865x_event_Head_t;

typedef struct rtl865x_eventLayerList_s
{
	int32 eventLayerId;
	rtl865x_event_Head_t eventHead; 
	CTAILQ_ENTRY(rtl865x_eventLayerList_s) next;
}rtl865x_eventLayerList_t;

typedef CTAILQ_HEAD(_eventLayerList_head_s, rtl865x_eventLayerList_s) rtl865x_eventLayerList_Head_t;
	
struct rtl865x_eventTables_s {
	struct freeEntryList_s {
		rtl865x_event_Head_t eventHead;
		rtl865x_eventLayerList_Head_t eventLayerListHead;
	} freeList;

	struct inuseEntryList_s {
		rtl865x_eventLayerList_Head_t	eventLayerListHead;
	} inuseList;

};

int32 rtl865x_initEventMgr(rtl865x_eventMgr_param_t *param);
int32 rtl865x_reInitEventMgr(void);
int32 rtl865x_registerEvent(rtl865x_event_Param_t *eventParam);
int32 rtl865x_unRegisterEvent(rtl865x_event_Param_t *eventParam);
int32  rtl865x_raiseEvent(int32 eventId,void *actionParam);
void rtl865x_dumpAllEventLayerListInfo(void);
int32 rtl865x_destroyEventMgr(void);

#ifdef CONFIG_RTL865X_EVENT_PROC_DEBUG
int32 rtl865x_event_proc_read( char *page, char **start, off_t off, int count, int *eof, void *data );
int32  rtl865x_event_proc_write( struct file *filp, const char *buff,unsigned long len, void *data );
#endif


#endif

