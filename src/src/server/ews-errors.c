/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the program; if not, see <http://www.gnu.org/licenses/>
 */

#include "evolution-ews-config.h"

#include "ews-errors.h"

static GHashTable *ews_error_hash = NULL;
static GOnce setup_error_once = G_ONCE_INIT;

static struct EwsErrorMap
ews_conn_errors[] =
{
	{"ErrorAccessDenied",					EWS_CONNECTION_ERROR_ACCESSDENIED},
	{"ErrorAccountDisabled",				EWS_CONNECTION_ERROR_ACCOUNTDISABLED},
	{"ErrorAddDelegatesFailed",				EWS_CONNECTION_ERROR_ADDDELEGATESFAILED},
	{"ErrorAddressSpaceNotFound",				EWS_CONNECTION_ERROR_ADDRESSSPACENOTFOUND},
	{"ErrorADOperation",					EWS_CONNECTION_ERROR_ADOPERATION},
	{"ErrorADSessionFilter",				EWS_CONNECTION_ERROR_ADSESSIONFILTER},
	{"ErrorADUnavailable",					EWS_CONNECTION_ERROR_ADUNAVAILABLE},
	{"ErrorAffectedTaskOccurrencesRequired",		EWS_CONNECTION_ERROR_AFFECTEDTASKOCCURRENCESREQUIRED},
	{"ErrorAttachmentSizeLimitExceeded",			EWS_CONNECTION_ERROR_ATTACHMENTSIZELIMITEXCEEDED},
	{"ErrorAutoDiscoverFailed",				EWS_CONNECTION_ERROR_AUTODISCOVERFAILED},
	{"ErrorAvailabilityConfigNotFound",			EWS_CONNECTION_ERROR_AVAILABILITYCONFIGNOTFOUND},
	{"ErrorBatchProcessingStopped",				EWS_CONNECTION_ERROR_BATCHPROCESSINGSTOPPED},
	{"ErrorCalendarCannotMoveOrCopyOccurrence",		EWS_CONNECTION_ERROR_CALENDARCANNOTMOVEORCOPYOCCURRENCE},
	{"ErrorCalendarCannotUpdateDeletedItem",		EWS_CONNECTION_ERROR_CALENDARCANNOTUPDATEDELETEDITEM},
	{"ErrorCalendarCannotUseIdForOccurrenceId",		EWS_CONNECTION_ERROR_CALENDARCANNOTUSEIDFOROCCURRENCEID},
	{"ErrorCalendarCannotUseIdForRecurringMasterId",	EWS_CONNECTION_ERROR_CALENDARCANNOTUSEIDFORRECURRINGMASTERID},
	{"ErrorCalendarDurationIsTooLong",			EWS_CONNECTION_ERROR_CALENDARDURATIONISTOOLONG},
	{"ErrorCalendarEndDateIsEarlierThanStartDate",		EWS_CONNECTION_ERROR_CALENDARENDDATEISEARLIERTHANSTARTDATE},
	{"ErrorCalendarFolderIsInvalidForCalendarView",		EWS_CONNECTION_ERROR_CALENDARFOLDERISINVALIDFORCALENDARVIEW},
	{"ErrorCalendarInvalidDayForTimeChangePattern",		EWS_CONNECTION_ERROR_CALENDARINVALIDDAYFORTIMECHANGEPATTERN},
	{"ErrorCalendarInvalidDayForWeeklyRecurrence",		EWS_CONNECTION_ERROR_CALENDARINVALIDDAYFORWEEKLYRECURRENCE},
	{"ErrorCalendarInvalidPropertyState",			EWS_CONNECTION_ERROR_CALENDARINVALIDPROPERTYSTATE},
	{"ErrorCalendarInvalidPropertyValue",			EWS_CONNECTION_ERROR_CALENDARINVALIDPROPERTYVALUE},
	{"ErrorCalendarInvalidRecurrence",			EWS_CONNECTION_ERROR_CALENDARINVALIDRECURRENCE},
	{"ErrorCalendarInvalidTimeZone",			EWS_CONNECTION_ERROR_CALENDARINVALIDTIMEZONE},
	{"ErrorCalendarIsDelegatedForAccept",			EWS_CONNECTION_ERROR_CALENDARISDELEGATEDFORACCEPT},
	{"ErrorCalendarIsDelegatedForDecline",			EWS_CONNECTION_ERROR_CALENDARISDELEGATEDFORDECLINE},
	{"ErrorCalendarIsDelegatedForRemove",			EWS_CONNECTION_ERROR_CALENDARISDELEGATEDFORREMOVE},
	{"ErrorCalendarIsDelegatedForTentative",		EWS_CONNECTION_ERROR_CALENDARISDELEGATEDFORTENTATIVE},
	{"ErrorCalendarIsNotOrganizer",				EWS_CONNECTION_ERROR_CALENDARISNOTORGANIZER},
	{"ErrorCalendarIsOrganizerForAccept",			EWS_CONNECTION_ERROR_CALENDARISORGANIZERFORACCEPT},
	{"ErrorCalendarIsOrganizerForDecline",			EWS_CONNECTION_ERROR_CALENDARISORGANIZERFORDECLINE},
	{"ErrorCalendarIsOrganizerForRemove",			EWS_CONNECTION_ERROR_CALENDARISORGANIZERFORREMOVE},
	{"ErrorCalendarIsOrganizerForTentative",		EWS_CONNECTION_ERROR_CALENDARISORGANIZERFORTENTATIVE},
	{"ErrorCalendarMeetingRequestIsOutOfDate",		EWS_CONNECTION_ERROR_CALENDARMEETINGREQUESTISOUTOFDATE},
	{"ErrorCalendarOccurrenceIndexIsOutOfRecurrenceRange",	EWS_CONNECTION_ERROR_CALENDAROCCURRENCEINDEXISOUTOFRECURRENCERANGE},
	{"ErrorCalendarOccurrenceIsDeletedFromRecurrence",	EWS_CONNECTION_ERROR_CALENDAROCCURRENCEISDELETEDFROMRECURRENCE},
	{"ErrorCalendarOutOfRange",				EWS_CONNECTION_ERROR_CALENDAROUTOFRANGE},
	{"ErrorCalendarViewRangeTooBig",			EWS_CONNECTION_ERROR_CALENDARVIEWRANGETOOBIG},
	{"ErrorCannotCreateCalendarItemInNonCalendarFolder",	EWS_CONNECTION_ERROR_CANNOTCREATECALENDARITEMINNONCALENDARFOLDER},
	{"ErrorCannotCreateContactInNonContactFolder",		EWS_CONNECTION_ERROR_CANNOTCREATECONTACTINNONCONTACTFOLDER},
	{"ErrorCannotCreatePostItemInNonMailFolder",		EWS_CONNECTION_ERROR_CANNOTCREATEPOSTITEMINNONMAILFOLDER},
	{"ErrorCannotCreateTaskInNonTaskFolder",		EWS_CONNECTION_ERROR_CANNOTCREATETASKINNONTASKFOLDER},
	{"ErrorCannotDeleteObject",				EWS_CONNECTION_ERROR_CANNOTDELETEOBJECT},
	{"ErrorCannotDeleteTaskOccurrence",			EWS_CONNECTION_ERROR_CANNOTDELETETASKOCCURRENCE},
	{"ErrorCannotOpenFileAttachment",			EWS_CONNECTION_ERROR_CANNOTOPENFILEATTACHMENT},
	{"ErrorCannotSetCalendarPermissionOnNonCalendarFolder",	EWS_CONNECTION_ERROR_CANNOTSETCALENDARPERMISSIONONNONCALENDARFOLDER},
	{"ErrorCannotSetNonCalendarPermissionOnCalendarFolder",	EWS_CONNECTION_ERROR_CANNOTSETNONCALENDARPERMISSIONONCALENDARFOLDER},
	{"ErrorCannotSetPermissionUnknownEntries",		EWS_CONNECTION_ERROR_CANNOTSETPERMISSIONUNKNOWNENTRIES},
	{"ErrorCannotUseFolderIdForItemId",			EWS_CONNECTION_ERROR_CANNOTUSEFOLDERIDFORITEMID},
	{"ErrorCannotUseItemIdForFolderId",			EWS_CONNECTION_ERROR_CANNOTUSEITEMIDFORFOLDERID},
	{"ErrorChangeKeyRequired",				EWS_CONNECTION_ERROR_CHANGEKEYREQUIRED},
	{"ErrorChangeKeyRequiredForWriteOperations",		EWS_CONNECTION_ERROR_CHANGEKEYREQUIREDFORWRITEOPERATIONS},
	{"ErrorConnectionFailed",				EWS_CONNECTION_ERROR_CONNECTIONFAILED},
	{"ErrorContentConversionFailed",			EWS_CONNECTION_ERROR_CONTENTCONVERSIONFAILED},
	{"ErrorCorruptData",					EWS_CONNECTION_ERROR_CORRUPTDATA},
	{"ErrorCreateItemAccessDenied",				EWS_CONNECTION_ERROR_CREATEITEMACCESSDENIED},
	{"ErrorCreateManagedFolderPartialCompletion",		EWS_CONNECTION_ERROR_CREATEMANAGEDFOLDERPARTIALCOMPLETION},
	{"ErrorCreateSubfolderAccessDenied",			EWS_CONNECTION_ERROR_CREATESUBFOLDERACCESSDENIED},
	{"ErrorCrossMailboxMoveCopy",				EWS_CONNECTION_ERROR_CROSSMAILBOXMOVECOPY},
	{"ErrorDataSizeLimitExceeded",				EWS_CONNECTION_ERROR_DATASIZELIMITEXCEEDED},
	{"ErrorDataSourceOperation",				EWS_CONNECTION_ERROR_DATASOURCEOPERATION},
	{"ErrorDelegateAlreadyExists",				EWS_CONNECTION_ERROR_DELEGATEALREADYEXISTS},
	{"ErrorDelegateCannotAddOwner",				EWS_CONNECTION_ERROR_DELEGATECANNOTADDOWNER},
	{"ErrorDelegateMissingConfiguration",			EWS_CONNECTION_ERROR_DELEGATEMISSINGCONFIGURATION},
	{"ErrorDelegateNoUser",					EWS_CONNECTION_ERROR_DELEGATENOUSER},
	{"ErrorDelegateValidationFailed",			EWS_CONNECTION_ERROR_DELEGATEVALIDATIONFAILED},
	{"ErrorDeleteDistinguishedFolder",			EWS_CONNECTION_ERROR_DELETEDISTINGUISHEDFOLDER},
	{"ErrorDistinguishedUserNotSupported",			EWS_CONNECTION_ERROR_DISTINGUISHEDUSERNOTSUPPORTED},
	{"ErrorDuplicateInputFolderNames",			EWS_CONNECTION_ERROR_DUPLICATEINPUTFOLDERNAMES},
	{"ErrorDuplicateUserIdsSpecified",			EWS_CONNECTION_ERROR_DUPLICATEUSERIDSSPECIFIED},
	{"ErrorEmailAddressMismatch",				EWS_CONNECTION_ERROR_EMAILADDRESSMISMATCH},
	{"ErrorEventNotFound",					EWS_CONNECTION_ERROR_EVENTNOTFOUND},
	{"ErrorExpiredSubscription",				EWS_CONNECTION_ERROR_EXPIREDSUBSCRIPTION},
	{"ErrorFolderCorrupt",					EWS_CONNECTION_ERROR_FOLDERCORRUPT},
	{"ErrorFolderExists",					EWS_CONNECTION_ERROR_FOLDEREXISTS},
	{"ErrorFolderNotFound",					EWS_CONNECTION_ERROR_FOLDERNOTFOUND},
	{"ErrorFolderPropertRequestFailed",			EWS_CONNECTION_ERROR_FOLDERPROPERTREQUESTFAILED},
	{"ErrorFolderSave",					EWS_CONNECTION_ERROR_FOLDERSAVE},
	{"ErrorFolderSaveFailed",				EWS_CONNECTION_ERROR_FOLDERSAVEFAILED},
	{"ErrorFolderSavePropertyError",			EWS_CONNECTION_ERROR_FOLDERSAVEPROPERTYERROR},
	{"ErrorFreeBusyGenerationFailed",			EWS_CONNECTION_ERROR_FREEBUSYGENERATIONFAILED},
	{"ErrorImpersonateUserDenied",				EWS_CONNECTION_ERROR_IMPERSONATEUSERDENIED},
	{"ErrorImpersonationDenied",				EWS_CONNECTION_ERROR_IMPERSONATIONDENIED},
	{"ErrorImpersonationFailed",				EWS_CONNECTION_ERROR_IMPERSONATIONFAILED},
	{"ErrorIncorrectSchemaVersion",				EWS_CONNECTION_ERROR_INCORRECTSCHEMAVERSION},
	{"ErrorIncorrectUpdatePropertyCount",			EWS_CONNECTION_ERROR_INCORRECTUPDATEPROPERTYCOUNT},
	{"ErrorIndividualMailboxLimitReached",			EWS_CONNECTION_ERROR_INDIVIDUALMAILBOXLIMITREACHED},
	{"ErrorInsufficientResources",				EWS_CONNECTION_ERROR_INSUFFICIENTRESOURCES},
	{"ErrorInternalServerError",				EWS_CONNECTION_ERROR_INTERNALSERVERERROR},
	{"ErrorInternalServerTransientError",			EWS_CONNECTION_ERROR_INTERNALSERVERTRANSIENTERROR},
	{"ErrorInvalidAccessLevel",				EWS_CONNECTION_ERROR_INVALIDACCESSLEVEL},
	{"ErrorInvalidAttachmentId",				EWS_CONNECTION_ERROR_INVALIDATTACHMENTID},
	{"ErrorInvalidAttachmentSubfilter",			EWS_CONNECTION_ERROR_INVALIDATTACHMENTSUBFILTER},
	{"ErrorInvalidAttachmentSubfilterTextFilter",		EWS_CONNECTION_ERROR_INVALIDATTACHMENTSUBFILTERTEXTFILTER},
	{"ErrorInvalidAuthorizationContext",			EWS_CONNECTION_ERROR_INVALIDAUTHORIZATIONCONTEXT},
	{"ErrorInvalidChangeKey",				EWS_CONNECTION_ERROR_INVALIDCHANGEKEY},
	{"ErrorInvalidClientSecurityContext",			EWS_CONNECTION_ERROR_INVALIDCLIENTSECURITYCONTEXT},
	{"ErrorInvalidCompleteDate",				EWS_CONNECTION_ERROR_INVALIDCOMPLETEDATE},
	{"ErrorInvalidCrossForestCredentials",			EWS_CONNECTION_ERROR_INVALIDCROSSFORESTCREDENTIALS},
	{"ErrorInvalidDelegatePermission",			EWS_CONNECTION_ERROR_INVALIDDELEGATEPERMISSION},
	{"ErrorInvalidDelegateUserId",				EWS_CONNECTION_ERROR_INVALIDDELEGATEUSERID},
	{"ErrorInvalidExchangeImpersonationHeaderData",		EWS_CONNECTION_ERROR_INVALIDEXCHANGEIMPERSONATIONHEADERDATA},
	{"ErrorInvalidExcludesRestriction",			EWS_CONNECTION_ERROR_INVALIDEXCLUDESRESTRICTION},
	{"ErrorInvalidExtendedProperty",			EWS_CONNECTION_ERROR_INVALIDEXTENDEDPROPERTY},
	{"ErrorInvalidExtendedPropertyValue",			EWS_CONNECTION_ERROR_INVALIDEXTENDEDPROPERTYVALUE},
	{"ErrorInvalidFolderId",				EWS_CONNECTION_ERROR_INVALIDFOLDERID},
	{"ErrorInvalidFolderTypeForOperation",			EWS_CONNECTION_ERROR_INVALIDFOLDERTYPEFOROPERATION},
	{"ErrorInvalidFractionalPagingParameters",		EWS_CONNECTION_ERROR_INVALIDFRACTIONALPAGINGPARAMETERS},
	{"ErrorInvalidFreeBusyViewType",			EWS_CONNECTION_ERROR_INVALIDFREEBUSYVIEWTYPE},
	{"ErrorInvalidId",					EWS_CONNECTION_ERROR_INVALIDID},
	{"ErrorInvalidIdEmpty",					EWS_CONNECTION_ERROR_INVALIDIDEMPTY},
	{"ErrorInvalidIdMalformed",				EWS_CONNECTION_ERROR_INVALIDIDMALFORMED},
	{"ErrorInvalidIdMalformedEwsLegacyIdFormat",		EWS_CONNECTION_ERROR_INVALIDIDMALFORMEDEWSLEGACYIDFORMAT},
	{"ErrorInvalidIdMonikerTooLong",			EWS_CONNECTION_ERROR_INVALIDIDMONIKERTOOLONG},
	{"ErrorInvalidIdNotAnItemAttachmentId",			EWS_CONNECTION_ERROR_INVALIDIDNOTANITEMATTACHMENTID},
	{"ErrorInvalidIdReturnedByResolveNames",		EWS_CONNECTION_ERROR_INVALIDIDRETURNEDBYRESOLVENAMES},
	{"ErrorInvalidIdStoreObjectIdTooLong",			EWS_CONNECTION_ERROR_INVALIDIDSTOREOBJECTIDTOOLONG},
	{"ErrorInvalidIdTooManyAttachmentLevels",		EWS_CONNECTION_ERROR_INVALIDIDTOOMANYATTACHMENTLEVELS},
	{"ErrorInvalidIndexedPagingParameters",			EWS_CONNECTION_ERROR_INVALIDINDEXEDPAGINGPARAMETERS},
	{"ErrorInvalidItemForOperationAcceptItem",		EWS_CONNECTION_ERROR_INVALIDITEMFOROPERATIONACCEPTITEM},
	{"ErrorInvalidItemForOperationCancelItem",		EWS_CONNECTION_ERROR_INVALIDITEMFOROPERATIONCANCELITEM},
	{"ErrorInvalidItemForOperationCreateItemAttachment",	EWS_CONNECTION_ERROR_INVALIDITEMFOROPERATIONCREATEITEMATTACHMENT},
	{"ErrorInvalidItemForOperationCreateItem",		EWS_CONNECTION_ERROR_INVALIDITEMFOROPERATIONCREATEITEM},
	{"ErrorInvalidItemForOperationDeclineItem",		EWS_CONNECTION_ERROR_INVALIDITEMFOROPERATIONDECLINEITEM},
	{"ErrorInvalidItemForOperationExpandDL",		EWS_CONNECTION_ERROR_INVALIDITEMFOROPERATIONEXPANDDL},
	{"ErrorInvalidItemForOperationRemoveItem",		EWS_CONNECTION_ERROR_INVALIDITEMFOROPERATIONREMOVEITEM},
	{"ErrorInvalidItemForOperationSendItem",		EWS_CONNECTION_ERROR_INVALIDITEMFOROPERATIONSENDITEM},
	{"ErrorInvalidItemForOperationTentative",		EWS_CONNECTION_ERROR_INVALIDITEMFOROPERATIONTENTATIVE},
	{"ErrorInvalidManagedFolderProperty",			EWS_CONNECTION_ERROR_INVALIDMANAGEDFOLDERPROPERTY},
	{"ErrorInvalidManagedFolderQuota",			EWS_CONNECTION_ERROR_INVALIDMANAGEDFOLDERQUOTA},
	{"ErrorInvalidManagedFolderSize",			EWS_CONNECTION_ERROR_INVALIDMANAGEDFOLDERSIZE},
	{"ErrorInvalidMergedFreeBusyInterval",			EWS_CONNECTION_ERROR_INVALIDMERGEDFREEBUSYINTERVAL},
	{"ErrorInvalidNameForNameResolution",			EWS_CONNECTION_ERROR_INVALIDNAMEFORNAMERESOLUTION},
	{"ErrorInvalidNetworkServiceContext",			EWS_CONNECTION_ERROR_INVALIDNETWORKSERVICECONTEXT},
	{"ErrorInvalidOperation",				EWS_CONNECTION_ERROR_INVALIDOPERATION},
	{"ErrorInvalidPagingMaxRows",				EWS_CONNECTION_ERROR_INVALIDPAGINGMAXROWS},
	{"ErrorInvalidParentFolder",				EWS_CONNECTION_ERROR_INVALIDPARENTFOLDER},
	{"ErrorInvalidPercentCompleteValue",			EWS_CONNECTION_ERROR_INVALIDPERCENTCOMPLETEVALUE},
	{"ErrorInvalidPermissionSettings",			EWS_CONNECTION_ERROR_INVALIDPERMISSIONSETTINGS},
	{"ErrorInvalidPropertyAppend",				EWS_CONNECTION_ERROR_INVALIDPROPERTYAPPEND},
	{"ErrorInvalidPropertyDelete",				EWS_CONNECTION_ERROR_INVALIDPROPERTYDELETE},
	{"ErrorInvalidPropertyForExists",			EWS_CONNECTION_ERROR_INVALIDPROPERTYFOREXISTS},
	{"ErrorInvalidPropertyForOperation",			EWS_CONNECTION_ERROR_INVALIDPROPERTYFOROPERATION},
	{"ErrorInvalidPropertyRequest",				EWS_CONNECTION_ERROR_INVALIDPROPERTYREQUEST},
	{"ErrorInvalidPropertySet",				EWS_CONNECTION_ERROR_INVALIDPROPERTYSET},
	{"ErrorInvalidPropertyUpdateSentMessage",		EWS_CONNECTION_ERROR_INVALIDPROPERTYUPDATESENTMESSAGE},
	{"ErrorInvalidPullSubscriptionId",			EWS_CONNECTION_ERROR_INVALIDPULLSUBSCRIPTIONID},
	{"ErrorInvalidPushSubscriptionUrl",			EWS_CONNECTION_ERROR_INVALIDPUSHSUBSCRIPTIONURL},
	{"ErrorInvalidRecipients",				EWS_CONNECTION_ERROR_INVALIDRECIPIENTS},
	{"ErrorInvalidRecipientSubfilter",			EWS_CONNECTION_ERROR_INVALIDRECIPIENTSUBFILTER},
	{"ErrorInvalidRecipientSubfilterComparison",		EWS_CONNECTION_ERROR_INVALIDRECIPIENTSUBFILTERCOMPARISON},
	{"ErrorInvalidRecipientSubfilterOrder",			EWS_CONNECTION_ERROR_INVALIDRECIPIENTSUBFILTERORDER},
	{"ErrorInvalidRecipientSubfilterTextFilter",		EWS_CONNECTION_ERROR_INVALIDRECIPIENTSUBFILTERTEXTFILTER},
	{"ErrorInvalidReferenceItem",				EWS_CONNECTION_ERROR_INVALIDREFERENCEITEM},
	{"ErrorInvalidRequest",					EWS_CONNECTION_ERROR_INVALIDREQUEST},
	{"ErrorInvalidRoutingType",				EWS_CONNECTION_ERROR_INVALIDROUTINGTYPE},
	{"ErrorInvalidScheduledOofDuration",			EWS_CONNECTION_ERROR_INVALIDSCHEDULEDOOFDURATION},
	{"ErrorInvalidSecurityDescriptor",			EWS_CONNECTION_ERROR_INVALIDSECURITYDESCRIPTOR},
	{"ErrorInvalidSendItemSaveSettings",			EWS_CONNECTION_ERROR_INVALIDSENDITEMSAVESETTINGS},
	{"ErrorInvalidSerializedAccessToken",			EWS_CONNECTION_ERROR_INVALIDSERIALIZEDACCESSTOKEN},
	{"ErrorInvalidSid",					EWS_CONNECTION_ERROR_INVALIDSID},
	{"ErrorInvalidServerVersion",				EWS_CONNECTION_ERROR_INVALIDSERVERVERSION},
	{"ErrorInvalidSmtpAddress",				EWS_CONNECTION_ERROR_INVALIDSMTPADDRESS},
	{"ErrorInvalidSubscription",				EWS_CONNECTION_ERROR_INVALIDSUBSCRIPTION},
	{"ErrorInvalidSubscriptionRequest",			EWS_CONNECTION_ERROR_INVALIDSUBSCRIPTIONREQUEST},
	{"ErrorInvalidSyncStateData",				EWS_CONNECTION_ERROR_INVALIDSYNCSTATEDATA},
	{"ErrorInvalidTimeInterval",				EWS_CONNECTION_ERROR_INVALIDTIMEINTERVAL},
	{"ErrorInvalidUserInfo",				EWS_CONNECTION_ERROR_INVALIDUSERINFO},
	{"ErrorInvalidUserOofSettings",				EWS_CONNECTION_ERROR_INVALIDUSEROOFSETTINGS},
	{"ErrorInvalidUserPrincipalName",			EWS_CONNECTION_ERROR_INVALIDUSERPRINCIPALNAME},
	{"ErrorInvalidUserSid",					EWS_CONNECTION_ERROR_INVALIDUSERSID},
	{"ErrorInvalidValueForProperty",			EWS_CONNECTION_ERROR_INVALIDVALUEFORPROPERTY},
	{"ErrorInvalidWatermark",				EWS_CONNECTION_ERROR_INVALIDWATERMARK},
	{"ErrorIrresolvableConflict",				EWS_CONNECTION_ERROR_IRRESOLVABLECONFLICT},
	{"ErrorItemCorrupt",					EWS_CONNECTION_ERROR_ITEMCORRUPT},
	{"ErrorItemNotFound",					EWS_CONNECTION_ERROR_ITEMNOTFOUND},
	{"ErrorItemPropertyRequestFailed",			EWS_CONNECTION_ERROR_ITEMPROPERTYREQUESTFAILED},
	{"ErrorItemSave",					EWS_CONNECTION_ERROR_ITEMSAVE},
	{"ErrorItemSavePropertyError",				EWS_CONNECTION_ERROR_ITEMSAVEPROPERTYERROR},
	{"ErrorLogonAsNetworkServiceFailed",			EWS_CONNECTION_ERROR_LOGONASNETWORKSERVICEFAILED},
	{"ErrorMailboxConfiguration",				EWS_CONNECTION_ERROR_MAILBOXCONFIGURATION},
	{"ErrorMailboxDataArrayEmpty",				EWS_CONNECTION_ERROR_MAILBOXDATAARRAYEMPTY},
	{"ErrorMailboxDataArrayTooBig",				EWS_CONNECTION_ERROR_MAILBOXDATAARRAYTOOBIG},
	{"ErrorMailboxLogonFailed",				EWS_CONNECTION_ERROR_MAILBOXLOGONFAILED},
	{"ErrorMailboxMoveInProgress",				EWS_CONNECTION_ERROR_MAILBOXMOVEINPROGRESS},
	{"ErrorMailboxStoreUnavailable",			EWS_CONNECTION_ERROR_MAILBOXSTOREUNAVAILABLE},
	{"ErrorMailRecipientNotFound",				EWS_CONNECTION_ERROR_MAILRECIPIENTNOTFOUND},
	{"ErrorManagedFolderAlreadyExists",			EWS_CONNECTION_ERROR_MANAGEDFOLDERALREADYEXISTS},
	{"ErrorManagedFolderNotFound",				EWS_CONNECTION_ERROR_MANAGEDFOLDERNOTFOUND},
	{"ErrorManagedFoldersRootFailure",			EWS_CONNECTION_ERROR_MANAGEDFOLDERSROOTFAILURE},
	{"ErrorMeetingSuggestionGenerationFailed",		EWS_CONNECTION_ERROR_MEETINGSUGGESTIONGENERATIONFAILED},
	{"ErrorMessageDispositionRequired",			EWS_CONNECTION_ERROR_MESSAGEDISPOSITIONREQUIRED},
	{"ErrorMessageSizeExceeded",				EWS_CONNECTION_ERROR_MESSAGESIZEEXCEEDED},
	{"ErrorMimeContentConversionFailed",			EWS_CONNECTION_ERROR_MIMECONTENTCONVERSIONFAILED},
	{"ErrorMimeContentInvalid",				EWS_CONNECTION_ERROR_MIMECONTENTINVALID},
	{"ErrorMimeContentInvalidBase64String",			EWS_CONNECTION_ERROR_MIMECONTENTINVALIDBASE64STRING},
	{"ErrorMissingArgument",				EWS_CONNECTION_ERROR_MISSINGARGUMENT},
	{"ErrorMissingEmailAddress",				EWS_CONNECTION_ERROR_MISSINGEMAILADDRESS},
	{"ErrorMissingEmailAddressForManagedFolder",		EWS_CONNECTION_ERROR_MISSINGEMAILADDRESSFORMANAGEDFOLDER},
	{"ErrorMissingInformationEmailAddress",			EWS_CONNECTION_ERROR_MISSINGINFORMATIONEMAILADDRESS},
	{"ErrorMissingInformationReferenceItemId",		EWS_CONNECTION_ERROR_MISSINGINFORMATIONREFERENCEITEMID},
	{"ErrorMissingItemForCreateItemAttachment",		EWS_CONNECTION_ERROR_MISSINGITEMFORCREATEITEMATTACHMENT},
	{"ErrorMissingManagedFolderId",				EWS_CONNECTION_ERROR_MISSINGMANAGEDFOLDERID},
	{"ErrorMissingRecipients",				EWS_CONNECTION_ERROR_MISSINGRECIPIENTS},
	{"ErrorMissingUserIdInformation",			EWS_CONNECTION_ERROR_MISSINGUSERIDINFORMATION},
	{"ErrorMoreThanOneAccessModeSpecified",			EWS_CONNECTION_ERROR_MORETHANONEACCESSMODESPECIFIED},
	{"ErrorMoveCopyFailed",					EWS_CONNECTION_ERROR_MOVECOPYFAILED},
	{"ErrorMoveDistinguishedFolder",			EWS_CONNECTION_ERROR_MOVEDISTINGUISHEDFOLDER},
	{"ErrorNameResolutionMultipleResults",			EWS_CONNECTION_ERROR_NAMERESOLUTIONMULTIPLERESULTS},
	{"ErrorNameResolutionNoMailbox",			EWS_CONNECTION_ERROR_NAMERESOLUTIONNOMAILBOX},
	{"ErrorNameResolutionNoResults",			EWS_CONNECTION_ERROR_NAMERESOLUTIONNORESULTS},
	{"ErrorNoCalendar",					EWS_CONNECTION_ERROR_NOCALENDAR},
	{"ErrorNoDestinationCASDueToKerberosRequirements",	EWS_CONNECTION_ERROR_NODESTINATIONCASDUETOKERBEROSREQUIREMENTS},
	{"ErrorNoDestinationCASDueToSSLRequirements",		EWS_CONNECTION_ERROR_NODESTINATIONCASDUETOSSLREQUIREMENTS},
	{"ErrorNoDestinationCASDueToVersionMismatch",		EWS_CONNECTION_ERROR_NODESTINATIONCASDUETOVERSIONMISMATCH},
	{"ErrorNoFolderClassOverride",				EWS_CONNECTION_ERROR_NOFOLDERCLASSOVERRIDE},
	{"ErrorNoFreeBusyAccess",				EWS_CONNECTION_ERROR_NOFREEBUSYACCESS},
	{"ErrorNonExistentMailbox",				EWS_CONNECTION_ERROR_NONEXISTENTMAILBOX},
	{"ErrorNonPrimarySmtpAddress",				EWS_CONNECTION_ERROR_NONPRIMARYSMTPADDRESS},
	{"ErrorNoPropertyTagForCustomProperties",		EWS_CONNECTION_ERROR_NOPROPERTYTAGFORCUSTOMPROPERTIES},
	{"ErrorNoRespondingCASInDestinationSite",		EWS_CONNECTION_ERROR_NORESPONDINGCASINDESTINATIONSITE},
	{"ErrorNotDelegate",					EWS_CONNECTION_ERROR_NOTDELEGATE},
	{"ErrorNotEnoughMemory",				EWS_CONNECTION_ERROR_NOTENOUGHMEMORY},
	{"ErrorObjectTypeChanged",				EWS_CONNECTION_ERROR_OBJECTTYPECHANGED},
	{"ErrorOccurrenceCrossingBoundary",			EWS_CONNECTION_ERROR_OCCURRENCECROSSINGBOUNDARY},
	{"ErrorOccurrenceTimeSpanTooBig",			EWS_CONNECTION_ERROR_OCCURRENCETIMESPANTOOBIG},
	{"ErrorOperationNotAllowedWithPublicFolderRoot",	EWS_CONNECTION_ERROR_OPERATIONNOTALLOWEDWITHPUBLICFOLDERROOT},
	{"ErrorParentFolderNotFound",				EWS_CONNECTION_ERROR_PARENTFOLDERNOTFOUND},
	{"ErrorPasswordChangeRequired",				EWS_CONNECTION_ERROR_PASSWORDCHANGEREQUIRED},
	{"ErrorPasswordExpired",				EWS_CONNECTION_ERROR_PASSWORDEXPIRED},
	{"ErrorPropertyUpdate",					EWS_CONNECTION_ERROR_PROPERTYUPDATE},
	{"ErrorProxiedSubscriptionCallFailure",			EWS_CONNECTION_ERROR_PROXIEDSUBSCRIPTIONCALLFAILURE},
	{"ErrorProxyGroupSidLimitExceeded",			EWS_CONNECTION_ERROR_PROXYGROUPSIDLIMITEXCEEDED},
	{"ErrorProxyRequestNotAllowed",				EWS_CONNECTION_ERROR_PROXYREQUESTNOTALLOWED},
	{"ErrorProxyRequestProcessingFailed",			EWS_CONNECTION_ERROR_PROXYREQUESTPROCESSINGFAILED},
	{"ErrorPublicFolderRequestProcessingFailed",		EWS_CONNECTION_ERROR_PUBLICFOLDERREQUESTPROCESSINGFAILED},
	{"ErrorPublicFolderServerNotFound",			EWS_CONNECTION_ERROR_PUBLICFOLDERSERVERNOTFOUND},
	{"ErrorQueryFilterTooLong",				EWS_CONNECTION_ERROR_QUERYFILTERTOOLONG},
	{"ErrorQuotaExceeded",					EWS_CONNECTION_ERROR_QUOTAEXCEEDED},
	{"ErrorReadEventsFailed",				EWS_CONNECTION_ERROR_READEVENTSFAILED},
	{"ErrorReadReceiptNotPending",				EWS_CONNECTION_ERROR_READRECEIPTNOTPENDING},
	{"ErrorRecurrenceEndDateTooBig",			EWS_CONNECTION_ERROR_RECURRENCEENDDATETOOBIG},
	{"ErrorRecurrenceHasNoOccurrence",			EWS_CONNECTION_ERROR_RECURRENCEHASNOOCCURRENCE},
	{"ErrorRemoveDelegatesFailed",				EWS_CONNECTION_ERROR_REMOVEDELEGATESFAILED},
	{"ErrorRequestStreamTooBig",				EWS_CONNECTION_ERROR_REQUESTSTREAMTOOBIG},
	{"ErrorRequiredPropertyMissing",			EWS_CONNECTION_ERROR_REQUIREDPROPERTYMISSING},
	{"ErrorResolveNamesInvalidFolderType",			EWS_CONNECTION_ERROR_RESOLVENAMESINVALIDFOLDERTYPE},
	{"ErrorResolveNamesOnlyOneContactsFolderAllowed",	EWS_CONNECTION_ERROR_RESOLVENAMESONLYONECONTACTSFOLDERALLOWED},
	{"ErrorResponseSchemaValidation",			EWS_CONNECTION_ERROR_RESPONSESCHEMAVALIDATION},
	{"ErrorRestrictionTooLong",				EWS_CONNECTION_ERROR_RESTRICTIONTOOLONG},
	{"ErrorRestrictionTooComplex",				EWS_CONNECTION_ERROR_RESTRICTIONTOOCOMPLEX},
	{"ErrorResultSetTooBig",				EWS_CONNECTION_ERROR_RESULTSETTOOBIG},
	{"ErrorSavedItemFolderNotFound",			EWS_CONNECTION_ERROR_SAVEDITEMFOLDERNOTFOUND},
	{"ErrorSchemaValidation",				EWS_CONNECTION_ERROR_SCHEMAVALIDATION},
	{"ErrorSearchFolderNotInitialized",			EWS_CONNECTION_ERROR_SEARCHFOLDERNOTINITIALIZED},
	{"ErrorSendAsDenied",					EWS_CONNECTION_ERROR_SENDASDENIED},
	{"ErrorSendMeetingCancellationsRequired",		EWS_CONNECTION_ERROR_SENDMEETINGCANCELLATIONSREQUIRED},
	{"ErrorSendMeetingInvitationsOrCancellationsRequired",	EWS_CONNECTION_ERROR_SENDMEETINGINVITATIONSORCANCELLATIONSREQUIRED},
	{"ErrorSendMeetingInvitationsRequired",			EWS_CONNECTION_ERROR_SENDMEETINGINVITATIONSREQUIRED},
	{"ErrorSentMeetingRequestUpdate",			EWS_CONNECTION_ERROR_SENTMEETINGREQUESTUPDATE},
	{"ErrorSentTaskRequestUpdate",				EWS_CONNECTION_ERROR_SENTTASKREQUESTUPDATE},
	{"ErrorServerBusy",					EWS_CONNECTION_ERROR_SERVERBUSY},
	{"ErrorServiceDiscoveryFailed",				EWS_CONNECTION_ERROR_SERVICEDISCOVERYFAILED},
	{"ErrorStaleObject",					EWS_CONNECTION_ERROR_STALEOBJECT},
	{"ErrorSubscriptionAccessDenied",			EWS_CONNECTION_ERROR_SUBSCRIPTIONACCESSDENIED},
	{"ErrorSubscriptionDelegateAccessNotSupported",		EWS_CONNECTION_ERROR_SUBSCRIPTIONDELEGATEACCESSNOTSUPPORTED},
	{"ErrorSubscriptionNotFound",				EWS_CONNECTION_ERROR_SUBSCRIPTIONNOTFOUND},
	{"ErrorSyncFolderNotFound",				EWS_CONNECTION_ERROR_SYNCFOLDERNOTFOUND},
	{"ErrorTimeIntervalTooBig",				EWS_CONNECTION_ERROR_TIMEINTERVALTOOBIG},
	{"ErrorTimeoutExpired",					EWS_CONNECTION_ERROR_TIMEOUTEXPIRED},
	{"ErrorTimeZone",					EWS_CONNECTION_ERROR_TIMEZONE},
	{"ErrorToFolderNotFound",				EWS_CONNECTION_ERROR_TOFOLDERNOTFOUND},
	{"ErrorTokenSerializationDenied",			EWS_CONNECTION_ERROR_TOKENSERIALIZATIONDENIED},
	{"ErrorUnsupportedCulture",				EWS_CONNECTION_ERROR_UNSUPPORTEDCULTURE},
	{"ErrorUnsupportedMapiPropertyType",			EWS_CONNECTION_ERROR_UNSUPPORTEDMAPIPROPERTYTYPE},
	{"ErrorUnsupportedMimeConversion",			EWS_CONNECTION_ERROR_UNSUPPORTEDMIMECONVERSION},
	{"ErrorUnsupportedPathForQuery",			EWS_CONNECTION_ERROR_UNSUPPORTEDPATHFORQUERY},
	{"ErrorUnsupportedPathForSortGroup",			EWS_CONNECTION_ERROR_UNSUPPORTEDPATHFORSORTGROUP},
	{"ErrorUnsupportedQueryFilter",				EWS_CONNECTION_ERROR_UNSUPPORTEDQUERYFILTER},
	{"ErrorUnsupportedRecurrence",				EWS_CONNECTION_ERROR_UNSUPPORTEDRECURRENCE},
	{"ErrorUnsupportedTypeForConversion",			EWS_CONNECTION_ERROR_UNSUPPORTEDTYPEFORCONVERSION},
	{"ErrorUpdateDelegatesFailed",				EWS_CONNECTION_ERROR_UPDATEDELEGATESFAILED},
	{"ErrorUpdatePropertyMismatch",				EWS_CONNECTION_ERROR_UPDATEPROPERTYMISMATCH},
	{"ErrorVirusDetected",					EWS_CONNECTION_ERROR_VIRUSDETECTED},
	{"ErrorVirusMessageDeleted",				EWS_CONNECTION_ERROR_VIRUSMESSAGEDELETED},
	{"ErrorWin32InteropError",				EWS_CONNECTION_ERROR_WIN32INTEROPERROR},
};

static gpointer
setup_error_map (gpointer data)
{
	gint i;

	ews_error_hash = g_hash_table_new (g_str_hash, g_str_equal);
	for (i = 0; i < G_N_ELEMENTS (ews_conn_errors); i++)
		g_hash_table_insert (
			ews_error_hash, (gpointer) ews_conn_errors[i].error_id,
			GINT_TO_POINTER (ews_conn_errors[i].error_code));
	return NULL;
}

gint
ews_get_error_code (const gchar *str)
{
	gint error_code = EWS_CONNECTION_ERROR_UNKNOWN;
	gpointer data;

	g_once (&setup_error_once, setup_error_map, NULL);

	data = g_hash_table_lookup (ews_error_hash, (gconstpointer) str);
	if (data)
		error_code = GPOINTER_TO_INT (data);

	return error_code;
}

gboolean
ews_get_response_status (ESoapParameter *param,
                         GError **error)
{
	ESoapParameter *subparam;
	gchar *value;
	gchar *message_text;
	gchar *response_code;
	gint error_code;
	gboolean success = TRUE;

	value = e_soap_parameter_get_property (param, "ResponseClass");
	g_return_val_if_fail (value != NULL, FALSE);

	if (g_ascii_strcasecmp (value, "Error") != 0)
		goto exit;

	subparam = e_soap_parameter_get_first_child_by_name (param, "MessageText");
	message_text = e_soap_parameter_get_string_value (subparam);

	subparam = e_soap_parameter_get_first_child_by_name (param, "ResponseCode");
	response_code = e_soap_parameter_get_string_value (subparam);
	error_code = ews_get_error_code (response_code);

	switch (error_code) {
		case EWS_CONNECTION_ERROR_CORRUPTDATA:
			/* FIXME: This happens because of a bug in the
			 * Exchange server, which doesn't like returning
			 * <Recurrence> for any appointment without a
			 * timezone, even if it's an all day event like a
			 * birthday. We need to handle the error and
			 * correctly report it to the user, but for now
			 * we'll just ignore it... */
			break;

		case EWS_CONNECTION_ERROR_INVALIDPROPERTYREQUEST:
			/* Ick, another one. If we try to set the IsRead
			 * flag on certain types of item (task requests,
			 * those stupid 'recall' requests), it complains.
			 * We really need to find a better way to return
			 * individual errors for each response to a multiple
			 * request; it isn't necessarily the case that a
			 * single error should be reported as an error for
			 * the whole transaction */
			break;

		default:
			g_set_error (
				error, EWS_CONNECTION_ERROR,
				error_code, "%s", message_text);
			success = FALSE;
			break;
	}

	g_free (message_text);
	g_free (response_code);

exit:
	g_free (value);

	return success;
}

