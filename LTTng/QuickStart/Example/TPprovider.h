
#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER example_provider

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./TPprovider.h"

#if !defined(TPPROVIDER_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define TPPROVIDER_H

#include <lttng/tracepoint.h>




TRACEPOINT_EVENT_CLASS
(
 example_provider,//tracepoint provider name
 myclass, //tracepoint class name
 TP_ARGS(
	 int, userid,
	 size_t, len
	 ),
 TP_FIELDS(
	 ctf_integer(int, userid, userid)
	 ctf_integer(size_t, len, len)
	 )

)


TRACEPOINT_EVENT_INSTANCE(
		example_provider,//provider name
		myclass, //clas name
		get_account,//tracepoint name
		TP_ARGS(
			int, userid,
			size_t, len
			)
)

TRACEPOINT_EVENT_INSTANCE(
		example_provider,//provider name
		myclass, //clas name
		get_setting,//tracepoint name
		TP_ARGS(
			int, userid,
			size_t, len
			)
)


TRACEPOINT_EVENT(
 example_provider,//tracepoint provider name
 number, // tracepoint name
 TP_ARGS
 ( //input arguments
	int, count,
	float, time,
	const char*, msg
 ),
 TP_FIELDS
 (
	ctf_string(msg_field, msg)
	ctf_float(double, time_field, time)
	ctf_integer(int, cnt_field, count)
	)

)








//TRACEPOINT_LOGLEVEL(example_provider, get_setting, TRACE_DEBUG_UNIT)

TRACEPOINT_LOGLEVEL(example_provider, get_setting, TRACE_DEBUG_UNIT)





#endif /* TPPROVIDER_H */

#include <lttng/tracepoint-event.h>
