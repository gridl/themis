/*
 * Copyright (c) 2017 Cossack Labs Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <assert.h>

#include <soter/soter_asym_key.h>
#include <soter/soter_container.h>
#include "soter_engine_consts.h"
#include "soter_x255519_key.h"
#include "soter_ed255519_key.h"

bool soter_key_is_private(const uint8_t* key, const size_t key_length){
  assert(key && key_length>sizeof(soter_container_hdr_t));
  assert(key[0]=='R' || key[0]=='U');
  return (key[0]=='R')?true:false;
}

int32_t soter_key_get_alg_id(const uint8_t* key, const size_t key_length){
  assert(key && key_length>sizeof(soter_container_hdr_t));
  if(0 == memcmp(key+1, "X2", 2)){
    return SOTER_ASYM_EC;
  }
  if (0 == memcmp(key+1, "ED", 2)){
    return SOTER_ASYM_RSA;
  }
  return 0;
}

int32_t soter_key_get_length_id(const uint8_t* key, const size_t key_length){
  assert(key && key_length>sizeof(soter_container_hdr_t));
  return (int32_t)(key[3]);
}

soter_status_t soter_key_pair_gen(int32_t alg_id, uint8_t* private_key, size_t* private_key_length, uint8_t* public_key, size_t* public_key_length){
  soter_status_t res = SOTER_SUCCESS;
  switch(alg_id&(SOTER_ASYM_ALGS|SOTER_ASYM_KEY_LENGTH)){
    SOTER_ED25519_KEY_GEN
    SOTER_X25519_KEY_GEN
  default:
    res = SOTER_INVALID_PARAMETER;
  }
  return res;
}

