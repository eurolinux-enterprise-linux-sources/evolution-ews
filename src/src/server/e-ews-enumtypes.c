
/* Generated data (by glib-mkenums) */

#include "e-ews-enumtypes.h"
/* enumerations from "./e-ews-enums.h" */
#include "./e-ews-enums.h"

GType
e_ews_external_audience_get_type (void)
{
	static volatile gsize the_type__volatile = 0;

	if (g_once_init_enter (&the_type__volatile)) {
		static const GEnumValue values[] = {
			{ E_EWS_EXTERNAL_AUDIENCE_NONE,
			  "E_EWS_EXTERNAL_AUDIENCE_NONE",
			  "none" },
			{ E_EWS_EXTERNAL_AUDIENCE_KNOWN,
			  "E_EWS_EXTERNAL_AUDIENCE_KNOWN",
			  "known" },
			{ E_EWS_EXTERNAL_AUDIENCE_ALL,
			  "E_EWS_EXTERNAL_AUDIENCE_ALL",
			  "all" },
			{ 0, NULL, NULL }
		};
		GType the_type = g_enum_register_static (
			g_intern_static_string ("EEwsExternalAudience"),
			values);
		g_once_init_leave (&the_type__volatile, the_type);
	}
	return the_type__volatile;
}

GType
e_ews_folder_type_get_type (void)
{
	static volatile gsize the_type__volatile = 0;

	if (g_once_init_enter (&the_type__volatile)) {
		static const GEnumValue values[] = {
			{ E_EWS_FOLDER_TYPE_UNKNOWN,
			  "E_EWS_FOLDER_TYPE_UNKNOWN",
			  "unknown" },
			{ E_EWS_FOLDER_TYPE_MAILBOX,
			  "E_EWS_FOLDER_TYPE_MAILBOX",
			  "mailbox" },
			{ E_EWS_FOLDER_TYPE_CALENDAR,
			  "E_EWS_FOLDER_TYPE_CALENDAR",
			  "calendar" },
			{ E_EWS_FOLDER_TYPE_CONTACTS,
			  "E_EWS_FOLDER_TYPE_CONTACTS",
			  "contacts" },
			{ E_EWS_FOLDER_TYPE_SEARCH,
			  "E_EWS_FOLDER_TYPE_SEARCH",
			  "search" },
			{ E_EWS_FOLDER_TYPE_TASKS,
			  "E_EWS_FOLDER_TYPE_TASKS",
			  "tasks" },
			{ E_EWS_FOLDER_TYPE_MEMOS,
			  "E_EWS_FOLDER_TYPE_MEMOS",
			  "memos" },
			{ 0, NULL, NULL }
		};
		GType the_type = g_enum_register_static (
			g_intern_static_string ("EEwsFolderType"),
			values);
		g_once_init_leave (&the_type__volatile, the_type);
	}
	return the_type__volatile;
}

GType
e_ews_oof_state_get_type (void)
{
	static volatile gsize the_type__volatile = 0;

	if (g_once_init_enter (&the_type__volatile)) {
		static const GEnumValue values[] = {
			{ E_EWS_OOF_STATE_DISABLED,
			  "E_EWS_OOF_STATE_DISABLED",
			  "disabled" },
			{ E_EWS_OOF_STATE_ENABLED,
			  "E_EWS_OOF_STATE_ENABLED",
			  "enabled" },
			{ E_EWS_OOF_STATE_SCHEDULED,
			  "E_EWS_OOF_STATE_SCHEDULED",
			  "scheduled" },
			{ 0, NULL, NULL }
		};
		GType the_type = g_enum_register_static (
			g_intern_static_string ("EEwsOofState"),
			values);
		g_once_init_leave (&the_type__volatile, the_type);
	}
	return the_type__volatile;
}


/* Generated data ends here */

