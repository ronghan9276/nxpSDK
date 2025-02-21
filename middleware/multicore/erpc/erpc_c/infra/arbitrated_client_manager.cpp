/*
 * The Clear BSD License
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
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
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
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

#include "arbitrated_client_manager.h"
#include "assert.h"
#include "transport_arbitrator.h"

using namespace erpc;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

#if ERPC_NESTED_CALLS_DETECTION
extern bool nestingDetection;
#pragma weak nestingDetection
bool nestingDetection = false;
#endif

void ArbitratedClientManager::setArbitrator(TransportArbitrator *arbitrator)
{
    m_arbitrator = arbitrator;
    m_transport = arbitrator;
}

erpc_status_t ArbitratedClientManager::performRequest(RequestContext &request)
{
    assert(m_arbitrator && "arbitrator not set");

    TransportArbitrator::client_token_t token = 0;

    // Set up the client receive before we send the request, so if the reply is sent
    // before we get to the clientReceive() call below the arbitrator already has the buffer.
    if (!request.isOneway())
    {
#if ERPC_NESTED_CALLS_DETECTION
        if (nestingDetection)
        {
            return kErpcStatus_NestedCallFailure;
        }
#endif
        token = m_arbitrator->prepareClientReceive(request);
        if (!token)
        {
            return kErpcStatus_Fail;
        }
    }

    erpc_status_t err;

#if ERPC_MESSAGE_LOGGING
    err = logMessage(request.getCodec()->getBuffer());
    if (err)
    {
        return err;
    }
#endif

    // Send the request.
    err = m_arbitrator->send(request.getCodec()->getBuffer());
    if (err)
    {
        return err;
    }

    if (!request.isOneway())
    {
        // Complete the receive through the arbitrator.
        err = m_arbitrator->clientReceive(token);
        if (err)
        {
            return err;
        }

#if ERPC_MESSAGE_LOGGING
        err = logMessage(request.getCodec()->getBuffer());
        if (err)
        {
            return err;
        }
#endif

        // Check the reply.
        err = verifyReply(request);
        if (err)
        {
            return err;
        }
    }

    return kErpcStatus_Success;
}
