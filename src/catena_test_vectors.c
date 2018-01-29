#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "catena.h"
#include "hash.h"

void print_hex(const char *message, const uint8_t *x, const int len)
{
  int i;
  puts(message);
    for(i=0; i< len; i++)
      {
	if((i!=0) && (i%8 == 0)) puts("");
	printf("%02x ",x[i]);
      }
    printf("     %d (octets)\n\n", len);
}

/*******************************************************************/

void test_output(const uint8_t *pwd,   const uint32_t pwdlen,
		 const uint8_t *salt,  const uint8_t saltlen,
		 const uint8_t *data,  const uint32_t datalen,
		 const uint8_t garlic, const uint8_t hashlen)
{
  uint8_t hash[hashlen];
  uint8_t h1test[hashlen];

  uint8_t* pwdcpy = malloc(pwdlen);
  strncpy((char*)pwdcpy, (char*)pwd, pwdlen);

  Catena((uint8_t*)pwdcpy, pwdlen, salt, saltlen, data, datalen,
	 LAMBDA, garlic, garlic, hashlen, hash);
  __Hash1((uint8_t*)pwdcpy, pwdlen, h1test);
  //__HashFast()

  print_hex("Password: ",pwd, pwdlen);
  print_hex("Salt: ",salt, saltlen);
  print_hex("Associated data:", data, datalen);
  printf("Lambda:  %u\n",LAMBDA);
  printf("(Min-)Garlic:  %u\n",garlic);
  print_hex("\nOutput: ", hash, hashlen);
  print_hex("\nBlake2s h1 test: " , h1test, hashlen);
  puts("\n\n");
}


/*******************************************************************/

void simpletest(const char *password, const char *salt, const char *header,
		uint8_t garlic)
{
  test_output((uint8_t *) password, strlen(password),
	      (uint8_t *) salt,     strlen(salt),
	      (uint8_t *) header,   strlen(header), garlic, H_LEN);
}


int main()
{
  simpletest("pass", "", "", 1);
  simpletest("password", "salt", "", 10);
  simpletest("password", "salt", "data", 10);

  simpletest("passwordPASSWORDpassword",
	     "saltSALTsaltSALTsaltSALTsaltSALTsalt","", 10);


  return 0;
}
