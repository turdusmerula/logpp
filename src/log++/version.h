/**
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
MA 02110-1301, USA.
*/


#ifndef _LOGPP_VERSION_H_
#define _LOGPP_VERSION_H_

#define LOGPP_VERSION_MAJOR 2
#define LOGPP_VERSION_MINOR 0
#define LOGPP_VERSION_PATCH 1


/**
 * LOGPP_CHECK_VERSION:
 * @major: major version (e.g. 1 for version 1.2.5)
 * @minor: minor version (e.g. 2 for version 1.2.5)
 * @micro: micro version (e.g. 5 for version 1.2.5)
 *
 * Returns %TRUE if the version of the GTK+ header files
 * is the same as or newer than the passed-in version.
 */
#define LOGPP_CHECK_VERSION(major,minor,patch)                          \
    (LOGPP_VERSION_MAJOR > (major) ||                                   \
     (LOGPP_VERSION_MAJOR == (major) && LOGPP_VERSION_MINOR > (minor)) || \
     (LOGPP_VERSION_MAJOR == (major) && LOGPP_VERSION_MINOR == (minor) && \
      LOGPP_VERSION_PATCH >= (patch)))

#endif
