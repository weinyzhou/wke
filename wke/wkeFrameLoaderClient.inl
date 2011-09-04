
#include <WebCore/DocumentLoader.h>
#include <WebCore/MIMETypeRegistry.h>
#include <WebCore/PluginData.h>
#include <WebCore/HTMLFrameOwnerElement.h>
#include <WebCore/PluginView.h>
#include <WebCore/HTMLPlugInElement.h>
#include <WebCore/FrameNetworkingContext.h>

namespace wke
{
    class FrameNetworkingContext : public WebCore::FrameNetworkingContext 
    {
    public:
        static PassRefPtr<FrameNetworkingContext> create(WebCore::Frame* frame)
        {
            return adoptRef(new FrameNetworkingContext(frame));
        }

    private:
        FrameNetworkingContext(WebCore::Frame* frame)
            : WebCore::FrameNetworkingContext(frame)
        {
        }

        virtual WTF::String userAgent() const override
        {
            return m_userAgent;
        }

        virtual WTF::String referrer() const override
        {
            return frame()->loader()->referrer();
        }

        virtual WebCore::ResourceError blockedError(const WebCore::ResourceRequest& request) const override
        {
            return frame()->loader()->client()->blockedError(request);
        }

        WTF::String m_userAgent;
    };

    class FrameLoaderClient : public WebCore::FrameLoaderClient
    {
    public:
        FrameLoaderClient(IWebView* webView, WebCore::Page* page)
            :webView_(webView)
            ,page_(page)
            ,frame_(NULL)
        {
        }

        virtual void frameLoaderDestroyed() override
        {
            dbgMsg("frameLoaderDestroyed");
            delete this;
        }

        virtual bool hasWebView() const override
        {
            return true;
        }

        virtual void makeRepresentation(WebCore::DocumentLoader*) override
        {
        }

        virtual void forceLayout() override
        {
        }

        virtual void forceLayoutForNonHTML() override
        {
        }

        virtual void setCopiesOnScroll() override
        {
        }

        virtual void detachedFromParent2() override
        {
        }

        virtual void detachedFromParent3() override
        {
        }

        virtual void assignIdentifierToInitialRequest(unsigned long identifier, WebCore::DocumentLoader*, const WebCore::ResourceRequest&) override
        {
        }

        virtual void dispatchWillSendRequest(WebCore::DocumentLoader*, unsigned long identifier, WebCore::ResourceRequest&, const WebCore::ResourceResponse& redirectResponse) override
        {
        }

        virtual bool shouldUseCredentialStorage(WebCore::DocumentLoader*, unsigned long identifier) override
        {
            return true;
        }

        virtual void dispatchDidReceiveAuthenticationChallenge(WebCore::DocumentLoader*, unsigned long identifier, const WebCore::AuthenticationChallenge&) override
        {
        }

        virtual void dispatchDidCancelAuthenticationChallenge(WebCore::DocumentLoader*, unsigned long identifier, const WebCore::AuthenticationChallenge&) override
        {
        }

#if USE(PROTECTION_SPACE_AUTH_CALLBACK)
        virtual bool canAuthenticateAgainstProtectionSpace(WebCore::DocumentLoader*, unsigned long identifier, const WebCore::ProtectionSpace&) override
        {
        }
#endif
        virtual void dispatchDidReceiveResponse(WebCore::DocumentLoader*, unsigned long identifier, const WebCore::ResourceResponse&) override
        {
        }

        virtual void dispatchDidReceiveContentLength(WebCore::DocumentLoader*, unsigned long identifier, int lengthReceived) override
        {
        }

        virtual void dispatchDidFinishLoading(WebCore::DocumentLoader*, unsigned long identifier) override
        {
        }

        virtual void dispatchDidFailLoading(WebCore::DocumentLoader*, unsigned long identifier, const WebCore::ResourceError&) override
        {
        }

        virtual bool dispatchDidLoadResourceFromMemoryCache(WebCore::DocumentLoader*, const WebCore::ResourceRequest&, const WebCore::ResourceResponse&, int length) override
        {
            return true;
        }

        virtual void dispatchDidHandleOnloadEvents() override
        {
        }

        virtual void dispatchDidReceiveServerRedirectForProvisionalLoad() override
        {
        }

        virtual void dispatchDidCancelClientRedirect() override
        {
        }

        virtual void dispatchWillPerformClientRedirect(const WebCore::KURL&, double interval, double fireDate) override
        {
        }

        virtual void dispatchDidChangeLocationWithinPage() override
        {
        }

        virtual void dispatchDidPushStateWithinPage() override
        {
        }

        virtual void dispatchDidReplaceStateWithinPage() override
        {
        }

        virtual void dispatchDidPopStateWithinPage() override
        {
        }

        virtual void dispatchWillClose() override
        {
        }

        virtual void dispatchDidReceiveIcon() override
        {
        }

        virtual void dispatchDidStartProvisionalLoad() override
        {
        }

        virtual void dispatchDidReceiveTitle(const WebCore::StringWithDirection& title) override
        {
        }

        virtual void dispatchDidChangeIcons(WebCore::IconType type) override
        {
        }

        virtual void dispatchDidCommitLoad() override
        {
        }

        virtual void dispatchDidFailProvisionalLoad(const WebCore::ResourceError&) override
        {
        }

        virtual void dispatchDidFailLoad(const WebCore::ResourceError&) override
        {
        }

        virtual void dispatchDidFinishDocumentLoad() override
        {
        }

        virtual void dispatchDidFinishLoad() override
        {
        }

        virtual void dispatchDidFirstLayout() override
        {
        }

        virtual void dispatchDidFirstVisuallyNonEmptyLayout() override
        {
        }

        virtual WebCore::Frame* dispatchCreatePage(const WebCore::NavigationAction&) override
        {
            return page_->mainFrame();
        }

        virtual void dispatchShow() override
        {
        }

        virtual void dispatchDecidePolicyForResponse(WebCore::FramePolicyFunction function, const WebCore::ResourceResponse&, const WebCore::ResourceRequest&) override
        {
            (frame_->loader()->policyChecker()->*function)(WebCore::PolicyUse);
        }

        virtual void dispatchDecidePolicyForNewWindowAction(WebCore::FramePolicyFunction function, const WebCore::NavigationAction&, const WebCore::ResourceRequest&, PassRefPtr<WebCore::FormState>, const WTF::String& frameName) override
        {
            (frame_->loader()->policyChecker()->*function)(WebCore::PolicyUse);
        }

        virtual void dispatchDecidePolicyForNavigationAction(WebCore::FramePolicyFunction function, const WebCore::NavigationAction&, const WebCore::ResourceRequest&, PassRefPtr<WebCore::FormState>) override
        {
            (frame_->loader()->policyChecker()->*function)(WebCore::PolicyUse);
        }

        virtual void cancelPolicyCheck() override
        {
        }

        virtual void dispatchUnableToImplementPolicy(const WebCore::ResourceError&) override
        {
        }

        virtual void dispatchWillSendSubmitEvent(WebCore::HTMLFormElement*) override
        {
        }

        virtual void dispatchWillSubmitForm(WebCore::FramePolicyFunction function, PassRefPtr<WebCore::FormState> formState) override
        {
            (frame_->loader()->policyChecker()->*function)(WebCore::PolicyUse);
        }

        virtual void dispatchDidLoadMainResource(WebCore::DocumentLoader*) override
        {
        }

        virtual void revertToProvisionalState(WebCore::DocumentLoader*) override
        {
        }

        virtual void setMainDocumentError(WebCore::DocumentLoader*, const WebCore::ResourceError&) override
        {
        }

        virtual void postProgressStartedNotification() override
        {
        }

        virtual void postProgressEstimateChangedNotification() override
        {
        }

        virtual void postProgressFinishedNotification() override
        {
        }
        
        virtual void setMainFrameDocumentReady(bool) override
        {
        }

        virtual void startDownload(const WebCore::ResourceRequest&, const String& suggestedName = String()) override
        {
            dbgMsg("startDownload\n");
        }

        virtual void willChangeTitle(WebCore::DocumentLoader*) override
        {
        }

        virtual void didChangeTitle(WebCore::DocumentLoader*) override
        {
        }

        virtual void committedLoad(WebCore::DocumentLoader* loader, const char* data, int length) override
        {
            loader->commitData(data, length);
        }

        virtual void finishedLoading(WebCore::DocumentLoader*) override
        {
        }
        
        virtual void updateGlobalHistory() override
        {
        }

        virtual void updateGlobalHistoryRedirectLinks() override
        {
        }

        virtual bool shouldGoToHistoryItem(WebCore::HistoryItem*) const override
        {
            return true;
        }

        virtual bool shouldStopLoadingForHistoryItem(WebCore::HistoryItem*) const override
        {
            return true;
        }

        virtual void dispatchDidAddBackForwardItem(WebCore::HistoryItem*) const override
        {
        }

        virtual void dispatchDidRemoveBackForwardItem(WebCore::HistoryItem*) const override
        {
        }

        virtual void dispatchDidChangeBackForwardIndex() const override
        {
        }

        virtual void didDisplayInsecureContent() override
        {
        }

        // The indicated security origin has run active content (such as a
        // script) from an insecure source.  Note that the insecure content can
        // spread to other frames in the same origin.
        virtual void didRunInsecureContent(WebCore::SecurityOrigin*, const WebCore::KURL&) override
        {
        }

        #define WebURLErrorDomain TEXT("WebURLErrorDomain")
        #define WebKitErrorDomain TEXT("WebKitErrorDomain")
        enum {
            WebURLErrorCancelled = -999,
            WebKitErrorCannotShowURL = 101,
            WebKitErrorFrameLoadInterruptedByPolicyChange = 102,
            WebKitErrorCannotUseRestrictedPort = 103,
            WebKitErrorPlugInWillHandleLoad = 204,
        };

        virtual WebCore::ResourceError cancelledError(const WebCore::ResourceRequest& request) override
        {
            return WebCore::ResourceError(String(WebURLErrorDomain), WebURLErrorCancelled, request.url().string(), String());
        }

        virtual WebCore::ResourceError blockedError(const WebCore::ResourceRequest& request) override
        {
            return WebCore::ResourceError(String(WebKitErrorDomain), WebKitErrorCannotUseRestrictedPort, request.url().string(), String());
        }

        virtual WebCore::ResourceError cannotShowURLError(const WebCore::ResourceRequest& request) override
        {
            return WebCore::ResourceError(String(WebKitErrorDomain), WebKitErrorCannotShowURL, request.url().string(), String());
        }

        virtual WebCore::ResourceError interruptedForPolicyChangeError(const WebCore::ResourceRequest& request) override
        {
            return WebCore::ResourceError(String(WebKitErrorDomain), WebKitErrorFrameLoadInterruptedByPolicyChange, request.url().string(), String());
        }

        virtual WebCore::ResourceError cannotShowMIMETypeError(const WebCore::ResourceResponse& response) override
        {
            return WebCore::ResourceError();
        }

        virtual WebCore::ResourceError fileDoesNotExistError(const WebCore::ResourceResponse& response) override
        {
            return WebCore::ResourceError();
        }

        virtual WebCore::ResourceError pluginWillHandleLoadError(const WebCore::ResourceResponse& response) override
        {
            return WebCore::ResourceError(String(WebKitErrorDomain), WebKitErrorPlugInWillHandleLoad, response.url().string(), String());
        }

        virtual bool shouldFallBack(const WebCore::ResourceError&) override
        {
            return false;
        }

        virtual bool canHandleRequest(const WebCore::ResourceRequest&) const override
        {
            return true;
        }

        virtual bool canShowMIMEType(const String& MIMEType) const override
        {
            return true;
        }

        virtual bool canShowMIMETypeAsHTML(const String& MIMEType) const override
        {
            return true;
        }

        virtual bool representationExistsForURLScheme(const WTF::String& URLScheme) const override
        {
            return false;
        }

        virtual WTF::String generatedMIMETypeForURLScheme(const WTF::String& URLScheme) const override
        {
            return String();
        }

        virtual void frameLoadCompleted() override
        {
        }

        virtual void saveViewStateToItem(WebCore::HistoryItem*) override
        {
        }
        
        virtual void restoreViewState() override
        {
        }

        virtual void provisionalLoadStarted() override
        {
        }
        
        virtual void didFinishLoad() override
        {
        }

        virtual void prepareForDataSourceReplacement() override
        {
        }

        virtual PassRefPtr<WebCore::DocumentLoader> createDocumentLoader(const WebCore::ResourceRequest& request, const WebCore::SubstituteData& data) override
        {
            return WebCore::DocumentLoader::create(request, data);
        }

        virtual void setTitle(const WebCore::StringWithDirection& title, const WebCore::KURL&) override
        {
        }

        virtual String userAgent(const WebCore::KURL&) override
        {
            return "Mozilla/5.0 (Windows NT 6.1) AppleWebKit/534+ (KHTML, like Gecko)";
        }
       
        virtual void savePlatformDataToCachedFrame(WebCore::CachedFrame*) override
        {
        }

        virtual void transitionToCommittedFromCachedFrame(WebCore::CachedFrame*) override
        {
        }

        virtual void transitionToCommittedForNewPage() override
        {
            bool transparent = false;
            WebCore::Color backgroundColor = WebCore::Color::white;

            WebCore::IntSize size(webView_->width(), webView_->height());
            frame_->createView(size, backgroundColor, transparent, WebCore::IntSize(), false);
        }

        virtual void didSaveToPageCache() override
        {
        }

        virtual void didRestoreFromPageCache() override
        {
        }

        virtual void dispatchDidBecomeFrameset(bool) override
        {
        }

        virtual bool canCachePage() const override
        {
            return false;
        }

        virtual void download(WebCore::ResourceHandle*, const WebCore::ResourceRequest&, const WebCore::ResourceRequest&, const WebCore::ResourceResponse&) override
        {
        }

        virtual PassRefPtr<WebCore::Frame> createFrame(const WebCore::KURL& url, const WTF::String& name, WebCore::HTMLFrameOwnerElement* ownerElement,
                                    const WTF::String& referrer, bool allowsScrolling, int marginWidth, int marginHeight) override
        {
            FrameLoaderClient* loader = new FrameLoaderClient(webView_, page_);
            RefPtr<WebCore::Frame> childFrame = WebCore::Frame::create(page_, ownerElement, loader);
            loader->setFrame(childFrame.get());

            frame_->tree()->appendChild(childFrame);
            childFrame->tree()->setName(name);
            childFrame->init();

            frame_->loader()->loadURLIntoChildFrame(url, referrer, childFrame.get());
            if (!childFrame->tree()->parent())
                return 0;

            return childFrame.release();
        }

        virtual void didTransferChildFrameToNewDocument(WebCore::Page*) override
        {
        }

        virtual void transferLoadingResourceFromPage(WebCore::ResourceLoader*, const WebCore::ResourceRequest&, WebCore::Page*) override
        {
        }

        virtual PassRefPtr<WebCore::Widget> createPlugin(const WebCore::IntSize& pluginSize, WebCore::HTMLPlugInElement* element, const WebCore::KURL& url, const Vector<String>& paramNames, const Vector<String>& paramValues, const String& mimeType, bool loadManually) override
        {
            Vector<String> newParamNames = paramNames;
            Vector<String> newParamValues = paramValues;

            unsigned i = 0;
            for (; i < newParamNames.size(); i++) {
                if (equalIgnoringCase(paramNames[i], "wmode"))
                    break;
            }

            if (i == newParamNames.size()) {
                newParamNames.append("wmode");
                newParamValues.append("opaque");
            }

            if (equalIgnoringCase(newParamValues[i], "window")) {
                newParamValues[i] = "opaque";
            }

            RefPtr<WebCore::PluginView> pluginView = WebCore::PluginView::create(frame_, pluginSize, element, url, newParamNames, newParamValues, mimeType, loadManually);
            if (pluginView->status() == WebCore::PluginStatusLoadedSuccessfully)
                return pluginView;

            return 0;
        }
        
        virtual void redirectDataToPlugin(WebCore::Widget* pluginWidget) override
        {
        }

        virtual PassRefPtr<WebCore::Widget> createJavaAppletWidget(const WebCore::IntSize&, WebCore::HTMLAppletElement*, const WebCore::KURL& baseURL, const Vector<WTF::String>& paramNames, const Vector<WTF::String>& paramValues) override
        {
            return 0;
        }

#if ENABLE(PLUGIN_PROXY_FOR_VIDEO)
        virtual PassRefPtr<WebCore::Widget> createMediaPlayerProxyPlugin(const WebCore::IntSize&, WebCore::HTMLMediaElement*, const WebCore::KURL&, const Vector<WTF::String>&, const Vector<WTF::String>&, const WTF::String&) override
        {
        }

        virtual void hideMediaPlayerProxyPlugin(WebCore::Widget*) override
        {
        }

        virtual void showMediaPlayerProxyPlugin(WebCore::Widget*) override
        {
        }
#endif

        virtual WebCore::ObjectContentType objectContentType(const WebCore::KURL& url, const WTF::String& mimeType, bool shouldPreferPlugInsForImages) override
        {
            return WebCore::FrameLoader::defaultObjectContentType(url, mimeType, shouldPreferPlugInsForImages);
        }

        virtual WTF::String overrideMediaType() const override
        {
            return WTF::String();
        }

        virtual void dispatchDidClearWindowObjectInWorld(WebCore::DOMWrapperWorld*) override
        {
        }

        virtual void documentElementAvailable() override
        {
        }

        virtual void didPerformFirstNavigation() const override
        {
        }

#if USE(V8)
        virtual void didCreateScriptContextForFrame() override
        {
        }

        virtual void didDestroyScriptContextForFrame() override
        {
        }

        virtual void didCreateIsolatedScriptContext() override
        {
        }

        virtual bool allowScriptExtension(const WTF::String& extensionName, int extensionGroup) override
        {
        }
#endif

        virtual void registerForIconNotification(bool listen = true) override
        {
        }

        virtual PassRefPtr<WebCore::FrameNetworkingContext> createNetworkingContext() override
        {
            return FrameNetworkingContext::create(frame_);
        }

        void setFrame(WebCore::Frame* frame)
        {
            frame_ = frame;
        }

        WebCore::Frame* frame() const
        {
            return frame_;
        }

    protected:
        IWebView* webView_;

        WebCore::Page* page_;
        WebCore::Frame* frame_;
    };
}