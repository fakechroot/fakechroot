/*
    libfakechroot -- fake chroot environment
    Copyright (c) 2010, 2013 Piotr Roszatycki <dexter@debian.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
*/


#include <config.h>

#include "libfakechroot.h"


wrapper(symlink, int, (const char * oldpath, const char * newpath))
{
    char tmp[FAKECHROOT_PATH_MAX];
    debug("symlink(\"%s\", \"%s\")", oldpath, newpath);
    char *noexpand_symlink_target = getenv("FAKECHROOT_NOEXPAND_SYMLINK_TARGET");
    if (!noexpand_symlink_target)
        expand_chroot_rel_path(oldpath);

    strcpy(tmp, oldpath);
    oldpath = tmp;
    expand_chroot_path(newpath);
    return nextcall(symlink)(oldpath, newpath);
}
