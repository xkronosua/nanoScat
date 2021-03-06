#ifndef __VERSION_H__
#define __VERSION_H__


#define MyAppVer "1.9-1"


// the debian changelog policy is used here so make sure:
//  you have the last version number matching between MyAppVersion and changelog
//  (the Linux Build index is derived from the changelog)
//  you dont touch the START and END changelog entries
//  date format is UNIX date -R  and there are two spaces between end of mail and date
//  there is NO blank line between the changelog start tag and the first entry !!!!
//
//START  changelog
//wxastrocapture (1.9-1) UNRELEASED; urgency=low
//
//   * Linux version now built under Kubuntu 12.04
//   * Compiled using wxWidgets 2.8.12
//
// -- C.Arnholm  M.Burri <wxAstroCapture@yahoogroups.com>  Tue, 30 Jun 2012 20:00:00 +0100
//
//wxastrocapture (1.8-1) UNRELEASED; urgency=low
//
//   * Linux version now built under Kubuntu 10.04 (Win version built under XP)
//   * Updated Win and Linux webcam streaming and capturing
//   * Added Win and Linux webcam FPS/DPS indicator (DPS=dropped frames per sec)
//   * Added Win and Linux performance switch to tune according to need and computer performance
//   * Added new and easier to use guiding options dialog
//   * Fixed layout issue for tabbed view (left side main window)
//   * Fixed LPT guite port settings issue on Linux (GX DEC neg not visible)
//   * Fixed issues with too many mandatory file name components
//   * Fixed issues with RGB capture on Win
//   * Fixed issue with capture gauge not ending after paused batch capture
//   * Fixed: Compiled wxWidgets 2.8.11 also on Linux (was 2.8.10 in 1.7-2)
//
// -- C.Arnholm  M.Burri <wxAstroCapture@yahoogroups.com>  Tue, 19 Oct 2010 20:00:00 +0100
//
//wxastrocapture (1.7-2) UNRELEASED; urgency=low
//
//   * Fixed .deb setup to be compliant with Ubuntu 8.10
//   * Fixed: Compiled wxWidgets 2.8.10 also on Linux (was 2.8.9 in 1.7-1)
//
// -- C.Arnholm  M.Burri <wxAstroCapture@yahoogroups.com>  Tue, 10 Nov 2009 20:00:00 +0100
//
//wxastrocapture (1.7-1) UNRELEASED; urgency=low
//
//   * Windows compiler change to VC2008. Users must install new vcredist_x86.exe.
//   * This version linked with wxWidgets 2.8.10 statically
//   * Added option to select in-frame timestamp Odd, Small, Medium
//   * Major update to camera handling, webcam resolutions prompted at startup
//   * Webcam resolution 640x480 is default when available in camera chooser
//   * New option on Rec tab to set predefined number of frames to capture
//   * Fixed issue with dual timestamps in file name
//   * Fixed issue with non-english locale causing problems with FITS headers
//   * Fixed Linux epm installer script for Kubuntu 9.10 udev handling
//   * Fixed missing config directory in new installation
//
// -- C.Arnholm  M.Burri <wxAstroCapture@yahoogroups.com>  Sun, 08 Nov 2009 20:00:00 +0100
//
//wxastrocapture (1.6-4) UNRELEASED; urgency=low
//
//   * Added timestamp_msec option to file name policy
//
// -- C.Arnholm  M.Burri <wxAstroCapture@yahoogroups.com>  Mon, 27 Jun 2009 20:00:00 +0100
//
//wxastrocapture (1.6-3) UNRELEASED; urgency=low
//
//   * Fixed parallelport detection problem on linux
//
// -- C.Arnholm  M.Burri <wxAstroCapture@yahoogroups.com>  Mon, 27 Apr 2009 20:00:00 +0100
//
//wxastrocapture (1.6-1) UNRELEASED; urgency=low
//
//   * This version built on WinXP SP3 and Kubuntu 8.04 (i386 and x64)
//   * This version linked with wxWidgets 2.8.9 statically
//   * Added batch capture feature
//   * Added Shoestring GPUSB support for guiding (Windows)
//   * Added Shoestring LXUSB support for webcam long exposure (Windows)
//   * Added Guiding driver for LX200 protocol that ends commands with :Qx#
//   * Replaced Linux SIO driver with USB native driver
//   * Fixed problem with needing libtiff4 under Linux (dependency removed)
//   * Fixed problem with capture timer display for webcams under Linux
//   * Fixed problem with Port Setup dialog not showing proper defaults after switching
//
// -- C.Arnholm  M.Burri <wxAstroCapture@yahoogroups.com>  Fri, 10 Apr 2009 20:00:00 +0100
//
//wxastrocapture (1.5-1) UNRELEASED; urgency=low
//
//   * This version built on WinXP SP3 and Kubuntu 8.04 (was 7.10 before)
//   * Fixed problem with capture prefix not taking immediate effect
//   * Fixed problem with object item in toolbar not editable
//   * Fixed problem with file name including %object% string just after first install
//   * Fixed problem with Fits header dialog showing nothing after first install
//
// -- C.Arnholm  M.Burri <wxAstroCapture@yahoogroups.com>  Wed, 15 Oct 2008 20:00:00 +0100
//
//wxastrocapture (1.4-1) UNRELEASED; urgency=low
//
//   * This version linked with wxWidgets 2.8.9 statically
//   * Fixed problem with non-functioning LX200 guiding
//   * Fixed problem with invisible mouse cursor for guiding autocalibration
//   * Added option to click OK in guiding autocalibration before reaching frame edge
//
// -- C.Arnholm  M.Burri <wxAstroCapture@yahoogroups.com>  Wed, 29 Sep 2008 20:00:00 +0100
//
//wxastrocapture (1.3-1) UNRELEASED; urgency=low
//
//   * Now automatically creates Linux - ~/.wxAstroCapture directory
//     on startup if missing
//   * Added saving plain FITS files in addition to the zipped archive
//   * Added pan, zoom, subframe for webcams
//   * Added option to pause & continue a capture sequence
//   * Added new capture filename policy (Settings dialog)
//   * Added capture frame counter in live image
//   * Fixed problem with crash on Win2000
//   * Added support for Trust webcam (under Win only, no Linux driver is known to us)
//
// -- C.Arnholm  M.Burri <wxAstroCapture@yahoogroups.com>  Wed, 16 Sep 2008 20:00:00 +0100
//
//wxastrocapture (1.1-1) UNRELEASED; urgency=low
//
//   * Added Binning ability for Artemis cameras
//   * Added Zoom ability for Artemis cameras
//   * Added Subframe ability for Artemis cameras
//   * Added toolbar with variable content, depending on camera model
//   * Added cooler control for Artemis cameras offering that feature
//   * Add Restart Button for Art (will abort the current take and start a new exposure)
//   * Switch capture on Artemis does not longer create one black image
//   * New Config setting for Linux - ~/.wxAstroCapture directory is used
//     config file name is now wxAstroCapture.conf (migration script exists)
//   * If any of the Art camera raw files are found in the UserDataDir
//     the CamSimulation is added to the cam enumerator
//   * Added RGB max values in histogram for webcams
//   * Support for Powerflex MTS guiding has been dropped (use V3 firmware w/LX200 instead)
//
// -- C.Arnholm  M.Burri <wxAstroCapture@yahoogroups.com>  Sun, 24 Feb 2008 20:00:00 +0100
//
//wxastrocapture (1.0-1) UNRELEASED; urgency=low
//
//   * Added support for Artemis cameras
//   * Added autoguiding
//   * Added dual instances can now be used
//
// -- C.Arnholm  M.Burri <wxAstroCapture@yahoogroups.com>  Fri, 06 Dec 2007 20:30:00 +0100
//
//wxastrocapture (0.9-1) UNRELEASED; urgency=low
//
//   * Beta build for external testing
//   * Added ZIP-FITS capture format
//   * Added Exposure meter feature
//   * Added Dialog for editing FITS header items (for FITS format)
//   * Video Properties dialog now remembers screen position
//
// -- C.Arnholm  M.Burri <wxAstroCapture@yahoogroups.com>  Mon, 24 Aug 2007 23:30:00 +0200
//
//wxastrocapture (0.8-2) UNRELEASED; urgency=low
//
//   * Beta build for external testing
//   * Correction for Linux segfault at startup
//
// -- C.Arnholm  M.Burri <wxAstroCapture@yahoogroups.com>  Mon, 09 Jul 2007 19:00:00 +0200
//
//wxastrocapture (0.8-1) UNRELEASED; urgency=low
//
//   * Beta build for external testing
//   * Modified SC webcam long exposure support
//   * Serial+parallel port control, user defined port configuration
//   * Save/restore of named slots for camera video properties
//   * Default slot for camera video properties
//
// -- C.Arnholm  M.Burri <wxAstroCapture@yahoogroups.com>  Fri, 06 Jul 2007 22:00:00 +0200
//
//wxastrocapture (0.4-1) UNRELEASED; urgency=low
//
//   * Beta build for external testing
//   * Now reports number of captured frames/elapsed time in status bar
//   * Added support for Windows 2000 (5.0.2195)
//
// -- C.Arnholm  M.Burri <wxAstroCapture@yahoogroups.com>  Sat, 09 Jun 2007 22:00:00 +0200
//
//wxastrocapture (0.3-1) UNRELEASED; urgency=low
//
//   * Beta build for external testing (basic app and install)
//   * Added support for uncompressed RGB capture
//
// -- C.Arnholm  M.Burri <abc@email.com>  Tue, 05 Jun 2007 00:12:00 +0200
//
//wxastrocapture (0.2-1) UNRELEASED; urgency=low
//
//   * Beta build for external testing (basic app and install)
//
// -- C.Arnholm  M.Burri <abc@email.com>  Sat, 02 Jun 2007 23:35:30 +0200
//
//wxastrocapture (0.1-1) UNRELEASED; urgency=low
//
//   * Initial test build
//
// -- C.Arnholm  M.Burri <abc@email.com>  Mon, 28 May 2007 23:28:55 +0200
//
//END changelog

#endif  // __VERSION_H__
