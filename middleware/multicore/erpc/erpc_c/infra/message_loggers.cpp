/*
 * The Clear BSD License
 * Copyright 2017 NXP
 * All rights reserved.
 *
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 * that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "message_loggers.h"
#include <new>

using namespace erpc;
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

MessageLoggers::~MessageLoggers()
{
    while (m_logger != NULL)
    {
        MessageLogger *logger = m_logger;
        m_logger = m_logger->getNext();
        delete logger;
    }
}

bool MessageLoggers::addMessageLogger(Transport *transport)
{
    if (transport != NULL)
    {
        MessageLogger *logger = new (nothrow) MessageLogger(transport);
        if (logger)
        {
            if (m_logger == NULL)
            {
                m_logger = logger;
                return true;
            }

            MessageLogger *_logger = m_logger;
            while (_logger->getNext() != NULL)
            {
                _logger = _logger->getNext();
            }

            _logger->setNext(logger);
            return true;
        }
    }
    return false;
}

erpc_status_t MessageLoggers::logMessage(MessageBuffer *msg)
{
    MessageLogger *_logger = m_logger;
    while (_logger != NULL)
    {
        if (erpc_status_t err = _logger->getLogger()->send(msg))
        {
            return err;
        }
        _logger = _logger->getNext();
    }
    return kErpcStatus_Success;
}
