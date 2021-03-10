/**       GNU GENERAL PUBLIC LICENSE, Version 3
 * Resource_Management - CPU usage limiter for windows (cygwin)
 * Copyright (C) 2012 Alexandre Quercia <alquerci@email.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// Les macros suivantes d?inissent la plateforme minimale requise. La plateforme minimale requise
// est la version de Windows, Internet Explorer etc. qui dispose des fonctionnalit? n?essaires pour ex?uter 
// votre application. Les macros fonctionnent en activant toutes les fonctionnalit? disponibles sur les versions de la plateforme jusqu'?la 
// version sp?ifi?.

// Modifiez les d?initions suivantes si vous devez cibler une plateforme avant celles sp?ifi?s ci-dessous.
// Reportez-vous ?MSDN pour obtenir les derni?es informations sur les valeurs correspondantes pour les diff?entes plateformes.
#ifndef _WIN32_WINNT            // Sp?ifie que la plateforme minimale requise est Windows Vista.
#define _WIN32_WINNT 0x0600     // Attribuez la valeur appropri? ?cet ??ent pour cibler d'autres versions de Windows.
#endif
