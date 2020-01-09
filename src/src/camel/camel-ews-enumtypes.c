
/* Generated data (by glib-mkenums) */

#include "camel-ews-enumtypes.h"
/* enumerations from "./camel-ews-enums.h" */
#include "./camel-ews-enums.h"

GType
camel_ews_store_ooo_alert_state_get_type (void)
{
	static volatile gsize the_type__volatile = 0;

	if (g_once_init_enter (&the_type__volatile)) {
		static const GEnumValue values[] = {
			{ CAMEL_EWS_STORE_OOO_ALERT_STATE_UNKNOWN,
			  "CAMEL_EWS_STORE_OOO_ALERT_STATE_UNKNOWN",
			  "unknown" },
			{ CAMEL_EWS_STORE_OOO_ALERT_STATE_NOTIFIED,
			  "CAMEL_EWS_STORE_OOO_ALERT_STATE_NOTIFIED",
			  "notified" },
			{ CAMEL_EWS_STORE_OOO_ALERT_STATE_CLOSED,
			  "CAMEL_EWS_STORE_OOO_ALERT_STATE_CLOSED",
			  "closed" },
			{ 0, NULL, NULL }
		};
		GType the_type = g_enum_register_static (
			g_intern_static_string ("CamelEwsStoreOooAlertState"),
			values);
		g_once_init_leave (&the_type__volatile, the_type);
	}
	return the_type__volatile;
}


/* Generated data ends here */

