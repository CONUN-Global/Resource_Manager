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

// Resource_Management.cpp : d?init le point d'entr? pour l'application console.
//

#include "stdafx.h"
#include <thread>
#include <iostream>
#include <string>

#define MAX_THREAD_COUNT    4096

typedef struct stArgument
{
    Config* Setting;
}_Argument;

unsigned int _stdcall ProcessLimit(LPVOID arg)
{
    Config *pSetting = (Config*)arg;

    //ProcessHandler* ph = new ProcessHandler(pSetting);
    ProcessHandler ph(pSetting);
    //ph(pSetting);

    if (ph.GetError())
    {
        //delete ph;
        delete pSetting;
        ExitProcess(EXIT_FAILURE);
    }
    MyExceptionHandler::SetProcessHandler(&ph);

    MyExceptionHandler::SignalRegister();

    while (ph.CheckState())
    {
        // Control process
        if (ph.IsOpen())
        {
            if (pSetting->GetTimeOff() > 0)
            {
                ph.Suspend();
                Sleep(pSetting->GetTimeOff());
                ph.Resume();
                Sleep(pSetting->GetTimeOn());
            }
            else
            {
                Sleep(Config::TIME_SLOT);
            }
        }
        else
        {
            // Wait process
            if (pSetting->GetLazy())
            {
                break;
            }
            Sleep(Config::TIME_SLOT * 2);
        }
    }

    //delete ph;

}

int main(int argc, char **argv)
{
    bool bRet = true;

    do
    {
        std::cout << "Input Process ID : ";
        std::cin >> argv[4];
        std::cout << "Input Limit Percent : ";
        std::cin >> argv[2];

        Config* settings = new Config(argc, argv);
        if (settings->GetError())
        {
            //Config::PrintUsage(stderr);
            delete settings;
            ExitProcess(EXIT_FAILURE);
        }
        MyExceptionHandler::SetConfig(settings);

        HANDLE hThread[MAX_THREAD_COUNT] = { 0, };

        for (int nLoop = 0; nLoop < MAX_THREAD_COUNT; nLoop++)
        {
            hThread[nLoop] = reinterpret_cast<HANDLE>(_beginthreadex(NULL, 0, ProcessLimit, settings, 0, NULL));
        }

        delete settings;
        //ExitProcess(EXIT_SUCCESS);

    } while (bRet == true);
}
