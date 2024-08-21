/*
 *
 *    Copyright (c) 2024 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#pragma once

#include "TermsAndConditionsProvider.h"

#include <stdint.h>

#include <lib/core/CHIPError.h>
#include <lib/core/CHIPPersistentStorageDelegate.h>
#include <lib/core/Optional.h>

namespace chip {
namespace app {
class DefaultTermsAndConditionsProvider : public TermsAndConditionsProvider
{
public:
    /**
     * @brief Initializes the TermsAndConditionsProvider.
     *
     * @param[in] inPersistentStorageDelegate Persistent storage delegate dependency.
     * @param[in] inRequiredAcknowledgementsValue The bitmask of required acknowledgements.
     * @param[in] inRequiredAcknowledgementsVersionValue The version of the required acknowledgements.
     */
    CHIP_ERROR Init(PersistentStorageDelegate * const inPersistentStorageDelegate, uint16_t inRequiredAcknowledgementsValue,
                    uint16_t inRequiredAcknowledgementsVersionValue);

    CHIP_ERROR CommitAcceptance() override;

    CHIP_ERROR GetAcceptance(uint16_t & outAcknowledgementsValue, uint16_t & outAcknowledgementsVersionValue) const override;

    CHIP_ERROR GetRequirements(uint16_t & outAcknowledgementsValue, uint16_t & outAcknowledgementsVersionValue) const override;

    CHIP_ERROR HasAcceptance(bool & outHasAcceptance) const override;

    CHIP_ERROR ResetAcceptance() override;

    CHIP_ERROR RevertAcceptance() override;

    CHIP_ERROR SetAcceptance(uint16_t inAcknowledgementsValue, uint16_t inAcknowledgementsVersionValue) override;

private:
    CHIP_ERROR LoadAcceptance(uint16_t & outAcknowledgementsValue, uint16_t & outAcknowledgementsVersionValue);

    CHIP_ERROR StoreAcceptance(uint16_t inAcknowledgementsValue, uint16_t inAcknowledgementsVersionValue);

    PersistentStorageDelegate * mPersistentStorageDelegate;
    uint16_t mRequiredAcknowledgementsValue;
    uint16_t mRequiredAcknowledgementsVersionValue;

    Optional<uint16_t> mLatchedAcknowledgementsAcceptanceValue;
    Optional<uint16_t> mLatchedAcknowledgementsAcceptanceVersionValue;

    Optional<uint16_t> mTemporaryAcknowledgementsAcceptanceValue;
    Optional<uint16_t> mTemporaryAcknowledgementsAcceptanceVersionValue;
};

} // namespace app
} // namespace chip
