%global evo_base_version 3.12
%global libmspack_version 0.4

Name: evolution-ews
Version: 3.12.11
Release: 9%{?dist}
Group: Applications/Productivity
Summary: Evolution extension for Exchange Web Services
License: LGPLv2
URL: https://wiki.gnome.org/Apps/Evolution
Source: http://download.gnome.org/sources/%{name}/3.12/%{name}-%{version}.tar.xz

# RH bug #1221520
Patch01: evolution-ews-3.12.11-translations.patch

# RH bug #1221876
Patch02: evolution-ews-3.12.11-book-lock-fix.patch

# Coverity Scan issues
Patch03: evolution-ews-3.12.11-coverity-scan.patch

# RH bug #1221520
Patch04: evolution-ews-3.12.11-translations2.patch

# RH bug #1322908
Patch05: evolution-ews-3.12.11-read-user-partstat.patch

Requires: evolution >= %{version}
Requires: evolution-data-server >= %{version}

%ifarch x86_64
Requires: libmspack >= %{libmspack_version}
%endif

BuildRequires: intltool
BuildRequires: pkgconfig(camel-1.2) >= %{version}
BuildRequires: pkgconfig(evolution-data-server-1.2) >= %{version}
BuildRequires: pkgconfig(evolution-mail-3.0) >= %{version}
BuildRequires: pkgconfig(evolution-shell-3.0) >= %{version}
BuildRequires: pkgconfig(glib-2.0)
BuildRequires: pkgconfig(gtk+-3.0)
BuildRequires: pkgconfig(libebackend-1.2) >= %{version}
BuildRequires: pkgconfig(libebook-1.2) >= %{version}
BuildRequires: pkgconfig(libecal-1.2) >= %{version}
BuildRequires: pkgconfig(libedata-book-1.2) >= %{version}
BuildRequires: pkgconfig(libedata-cal-1.2) >= %{version}
BuildRequires: pkgconfig(libemail-engine) >= %{version}
BuildRequires: pkgconfig(libical) >= 1.0
%ifarch x86_64
BuildRequires: pkgconfig(libmspack) >= %{libmspack_version}
%endif
BuildRequires: pkgconfig(libsoup-2.4)

%description
This package allows Evolution to interact with Microsoft Exchange servers,
versions 2007 and later, through its Exchange Web Services (EWS) interface.

%prep
%setup -q
%patch01 -p1 -b .translations
%patch02 -p1 -b .book-lock-fix
%patch03 -p1 -b .coverity-scan

# we got broken rendering for zh_TW.po
# this is creating issues for diff command
rm -f po/zh_TW.po

%patch04 -p1 -b .translations2
%patch05 -p1 -b .read-user-partstat

%build

export CFLAGS="$RPM_OPT_FLAGS -Wno-deprecated-declarations"
%ifarch x86_64
%configure
%else
%configure --with-internal-lzx
%endif
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT

# Remove files we don't want packaged (no devel subpackage).
rm -r $RPM_BUILD_ROOT%{_includedir}/evolution-data-server/
rm $RPM_BUILD_ROOT%{_libdir}/evolution-data-server/*.la
rm $RPM_BUILD_ROOT%{_libdir}/evolution-data-server/*.so
rm $RPM_BUILD_ROOT%{_libdir}/evolution-data-server/*/*.la
rm $RPM_BUILD_ROOT%{_libdir}/evolution/%{evo_base_version}/modules/*.la

%find_lang %{name}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files -f %{name}.lang
%defattr(-,root,root,-)
%doc COPYING NEWS README
%{_libdir}/evolution-data-server/libeews-1.2.so.*
%{_libdir}/evolution-data-server/libewsutils.so.*
%{_libdir}/evolution-data-server/camel-providers/libcamelews.so
%{_libdir}/evolution-data-server/camel-providers/libcamelews.urls
%{_libdir}/evolution-data-server/addressbook-backends/libebookbackendews.so
%{_libdir}/evolution-data-server/calendar-backends/libecalbackendews.so
%{_libdir}/evolution-data-server/registry-modules/module-ews-backend.so
%{_libdir}/evolution/%{evo_base_version}/modules/module-ews-configuration.so
%{_datadir}/appdata/evolution-ews.metainfo.xml
%{_datadir}/evolution/%{evo_base_version}/errors/module-ews-configuration.error
%{_datadir}/evolution-data-server/ews/windowsZones.xml

%changelog
* Tue Jun 21 2016 Milan Crha <mcrha@redhat.com> - 3.12.11-9
- Update patch for RH bug #1221520 (Update translations, for it and ko)

* Fri Apr 01 2016 Milan Crha <mcrha@redhat.com> - 3.12.11-8
- Add patch for RH bug #1322908 (Show user's meeting response in the Calendar view)

* Tue Mar 15 2016 Milan Crha <mcrha@redhat.com> - 3.12.11-7
- Add patch for RH bug #1221520 (Update translations)

* Fri Mar 04 2016 Milan Crha <mcrha@redhat.com> - 3.12.11-6
- Add dependency on libmspack 0.4+ for x86_64

* Wed Jul 08 2015 Milan Crha <mcrha@redhat.com> - 3.12.11-5
- Rebuild against updated libical

* Thu May 21 2015 Milan Crha <mcrha@redhat.com> - 3.12.11-4
- Add patch to address some of the Coverity Scan issues

* Fri May 15 2015 Milan Crha <mcrha@redhat.com> - 3.12.11-3
- Add patch for RH bug #1221876 (Correct locking in e_book_backend_ews_set_locale())

* Thu May 14 2015 Milan Crha <mcrha@redhat.com> - 3.12.11-2
- Add patch for RH bug #1221520 (Update translations)

* Mon May 04 2015 Milan Crha <mcrha@redhat.com> - 3.12.11-1
- Update to 3.12.11

* Fri Jan 24 2014 Daniel Mach <dmach@redhat.com> - 3.8.5-8
- Mass rebuild 2014-01-24

* Mon Jan 13 2014 Milan Crha <mcrha@redhat.com> - 3.8.5-7
- Add patch for RH bug #1030329 (Updated translations)

* Fri Dec 27 2013 Daniel Mach <dmach@redhat.com> - 3.8.5-6
- Mass rebuild 2013-12-27

* Tue Nov 19 2013 Milan Crha <mcrha@redhat.com> - 3.8.5-5
- Add patch for RH bug #1029538 (Free/Busy time is shifted)

* Tue Oct 15 2013 Milan Crha <mcrha@redhat.com> - 3.8.5-4
- Add patch for RH bug #1018322 (fails to get Free/Busy information)

* Tue Sep 10 2013 Milan Crha <mcrha@redhat.com> - 3.8.5-3
- Add patch for RH bug #1005152 (fails to download attachments)

* Fri Aug 16 2013 Milan Crha <mcrha@redhat.com> - 3.8.5-2
- Add patch to regression of GNOME bug #702922 (Cannot create appointments)

* Mon Aug 12 2013 Milan Crha <mcrha@redhat.com> - 3.8.5-1
- Update to 3.8.5

* Wed Jul 24 2013 Milan Crha <mcrha@redhat.com> - 3.8.4-1
- Update to 3.8.4

* Mon Jun 10 2013 Milan Crha <mcrha@redhat.com> - 3.8.3-1
- Update to 3.8.3

* Sun May 12 2013 Matthew Barnes <mbarnes@redhat.com> - 3.8.2-1
- Update to 3.8.2

* Sun Apr 14 2013 Matthew Barnes <mbarnes@redhat.com> - 3.8.1-1
- Update to 3.8.1

* Mon Mar 25 2013 Milan Crha <mcrha@redhat.com> - 3.8.0-1
- Update to 3.8.0

* Mon Mar 18 2013 Milan Crha <mcrha@redhat.com> - 3.7.92-1
- Update to 3.7.92

* Mon Mar 04 2013 Milan Crha <mcrha@redhat.com> - 3.7.91-1
- Update to 3.7.91

* Mon Feb 18 2013 Milan Crha <mcrha@redhat.com> - 3.7.90-1
- Update to 3.7.90

* Mon Feb 04 2013 Milan Crha <mcrha@redhat.com> - 3.7.5-1
- Update to 3.7.5

* Mon Jan 14 2013 Milan Crha <mcrha@redhat.com> - 3.7.4-1
- Update to 3.7.4

* Thu Dec 20 2012 Matthew Barnes <mbarnes@redhat.com> - 3.7.3.1-1
- Update to 3.7.3.1

* Mon Nov 19 2012 Milan Crha <mcrha@redhat.com> - 3.7.2-1
- Update to 3.7.2

* Mon Oct 22 2012 Milan Crha <mcrha@redhat.com> - 3.7.1-1
- Update to 3.7.1

* Mon Sep 17 2012 Milan Crha <mcrha@redhat.com> - 3.5.92-1
- Update to 3.5.92

* Mon Sep 03 2012 Milan Crha <mcrha@redhat.com> - 3.5.91-1
- Update to 3.5.91
- Remove patch for new xmlOutputBuffer API (fixed upstream)

* Mon Aug 20 2012 Milan Crha <mcrha@redhat.com> - 3.5.90-1
- Update to 3.5.90
- Add patch for new xmlOutputBuffer API

* Mon Aug 06 2012 Milan Crha <mcrha@redhat.com> - 3.5.5-1
- Update to 3.5.5

* Thu Jul 19 2012 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 3.5.4-2
- Rebuilt for https://fedoraproject.org/wiki/Fedora_18_Mass_Rebuild

* Mon Jul 16 2012 Milan Crha <mcrha@redhat.com> - 3.5.4-1
- Update to 3.5.4

* Mon Jun 25 2012 Matthew Barnes <mbarnes@redhat.com> - 3.5.3-1
- Update to 3.5.3

* Mon Jun 04 2012 Milan Crha <mcrha@redhat.com> - 3.5.2-1
- Update to 3.5.2

* Sun Apr 29 2012 Matthew Barnes <mbarnes@redhat.com> - 3.5.1-1
- Update to 3.5.1

* Mon Mar 26 2012 Milan Crha <mcrha@redhat.com> - 3.4.0-1
- Update to 3.4.0

* Mon Mar 19 2012 Milan Crha <mcrha@redhat.com> - 3.3.92-1
- Update to 3.3.92

* Tue Mar 06 2012 Milan Crha <mcrha@redhat.com> - 3.3.91-1
- Update to 3.3.91

* Mon Feb 20 2012 Milan Crha <mcrha@redhat.com> - 3.3.90-1
- Update to 3.3.90

* Mon Feb 06 2012 Milan Crha <mcrha@redhat.com> - 3.3.5-1
- Update to 3.3.5

* Mon Jan 16 2012 Milan Crha <mcrha@redhat.com> - 3.3.4-1
- Update to 3.3.4

* Fri Jan 13 2012 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 3.3.3-2
- Rebuilt for https://fedoraproject.org/wiki/Fedora_17_Mass_Rebuild

* Mon Dec 19 2011 Milan Crha <mcrha@redhat.com> - 3.3.3-1
- Update to 3.3.3
- Removed the last patch (fixed upstream)

* Mon Nov 21 2011 Milan Crha <mcrha@redhat.com> - 3.3.2-1
- Update to 3.3.2
- Removed obsolete patches (fixed upstream)

* Mon Nov 07 2011 Matthew Barnes <mbarnes@redhat.com> - 3.3.1-1
- Initial packaging for Fedora 17.
