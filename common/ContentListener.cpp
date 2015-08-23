/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Pioneer Research Center USA, Inc.
 * Portions created by the Initial Developer are Copyright (C) 2008
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *    Tristan Van Berkom <tristan.van.berkom@gmail.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
#if defined(WIN32)
#include "mozilla/Char16.h"
#endif

#include "ContentListener.h"
#include "embed.h"

#include "nsXULAppAPI.h"
#include "nsXPCOMGlue.h"
#include "nsStringAPI.h"
#include "nsCOMPtr.h"
#include "nsServiceManagerUtils.h"
#include "nsDocShellCID.h"

#include "nsILocalFile.h"
#include "nsIURI.h"
#include "nsIWebNavigationInfo.h"

ContentListener::ContentListener(MozView *aOwner, nsIWebNavigation *aNavigation)
{
    mOwner = aOwner;
    mNavigation = aNavigation;
}

ContentListener::~ContentListener()
{
}

NS_IMPL_ISUPPORTS(ContentListener,
                   nsIURIContentListener)
NS_IMETHODIMP
ContentListener::OnStartURIOpen(nsIURI *aURI, bool *aAbortOpen)
{
    nsresult rv;
    nsCString specString;
    rv = aURI->GetSpec(specString);
    if (NS_FAILED(rv)) return rv;

    MozViewListener *listener = mOwner->GetListener ();
    if (listener)
    {
    	const char* data;
    	uint32_t dataLen = NS_CStringGetData(specString, &data);

        *aAbortOpen = listener->OpenURI(data);
    }
    else
        *aAbortOpen = false;

    return NS_OK;
}

NS_IMETHODIMP
ContentListener::DoContent(
#if MOZILLA_VERSION_1 < 39
const char * /*aContentType*/,
#else
const nsACString& /*aContentType*/,
#endif
                           bool /*aIsContentPreferred*/,
                           nsIRequest * /*aRequest*/,
                           nsIStreamListener ** /*aContentHandler*/,
                           bool * /*aAbortProcess*/)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
ContentListener::IsPreferred(const char * aContentType,
                             char ** aDesiredContentType,
                             bool * aCanHandleContent)
{
    return CanHandleContent(aContentType, PR_TRUE, aDesiredContentType,
                            aCanHandleContent);
}

NS_IMETHODIMP
ContentListener::CanHandleContent(const char * aContentType,
                                  bool /*aIsContentPreferred*/,
                                  char ** aDesiredContentType,
                                  bool * _retval)
{
    *_retval = PR_FALSE;
    *aDesiredContentType = NULL;

    if (!aContentType)
        return NS_ERROR_FAILURE;

    nsCOMPtr<nsIWebNavigationInfo> webNavInfo(do_GetService(NS_WEBNAVIGATION_INFO_CONTRACTID));
    if (!webNavInfo)
        return NS_ERROR_FAILURE;

    PRUint32 canHandle;

    nsCString aContStr;
    aContStr.Assign(NS_LITERAL_CSTRING(aContentType));

    //nsresult rv = webNavInfo->IsTypeSupported(nsACString(aContentType),
    nsresult rv = webNavInfo->IsTypeSupported(aContStr,
                                        mNavigation ? mNavigation.get() : NULL,
                                        &canHandle);
    if (NS_FAILED(rv)) return rv;

    *_retval = (canHandle != nsIWebNavigationInfo::UNSUPPORTED);
    return NS_OK;
}

NS_IMETHODIMP
ContentListener::GetLoadCookie(nsISupports ** /*aLoadCookie*/)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
ContentListener::SetLoadCookie(nsISupports * /*aLoadCookie*/)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
ContentListener::GetParentContentListener(nsIURIContentListener ** /*aParent*/)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

NS_IMETHODIMP
ContentListener::SetParentContentListener(nsIURIContentListener * /*aParent*/)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

