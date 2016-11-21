/*

GarageCode Genial Creations Hehehe
http://BotecoUnix.com.br

*função do programa
Postar no twitter para mostrar um simples funcionamento de um Spider em linguagem C
usando lib Curl

*requerimentos
 libcurl-dev
 visit this site to many things "http://curl.haxx.se"

*tested with GCC 
 on Unix/Linux/*BSD this: 
    gcc -o program program.c -l curl; ./program     

Author: Antonio "Cooler_" 
contact: tony.unix@yahoo.com.br
license: BSD

visit this site: http://BotecoUnix.com.br
Real Geeks BotecoUnix

greetz 
Thanks muzgo,_mlk_ ,m0nad,IAK,Fox,D3lf0 and nibbles. 
K&R for book ansi C

      .--..--..--..--..--..--.
    .' \  (`._   (_)     _   \
  .'    |  '._)         (_)  |
  \ _.')\      .----..---.   /
  |(_.'  |    /    .-\-.  \  |
  \     0|    |   ( O| O) | o|
   |  _  |  .--.____.'._.-.  |
   \ (_) | o         -` .-`  |
    |    \   |`-._ _ _ _ _\ /
    \    |   |  `. |_||_|   |     Solution!
    | o  |    \_      \     |     -.   .-.
    |.-.  \     `--..-'   O |     `.`-' .'
  _.'  .' |     `-.-'      /-.__   ' .-'
.' `-.` '.|='=.='=.='=.='=|._/_ `-'.'
`-._  `.  |________/\_____|    `-.'
   .'   ).| '=' '='\/ '=' |
   `._.`  '---------------'
           //___\   //___\
             ||       ||
             ||_.-.   ||_.-.
            (_.--__) (_.--__)

*/
#include <stdio.h>
#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>

int main(int argc, char **argv) {
  //inicio declaramos vars,ponteiros...
    CURL *curl_handle;
    char * msg;
    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();
    CURLcode saida;
  //iniciamos o spider
  //definimos status para nosso post no twitter 
    msg ="status=twitter post with C Code by Cooler_";
  //passamos URL
    curl_easy_setopt(curl_handle, CURLOPT_URL, "http://twitter.com/statuses/update.json");
//    curl_easy_setopt(curl_handle, CURLOPT_RETURNTRANSFER, 1); 
    curl_easy_setopt(curl_handle, CURLOPT_CONNECTTIMEOUT, 2);
    curl_easy_setopt(curl_handle, CURLOPT_POST, 1);
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, msg);
  //definimos campos de login e senha
    curl_easy_setopt(curl_handle, CURLOPT_USERPWD, "Cooler_freenode:1234");
  //envia dados
    curl_easy_perform(curl_handle);
  //limpa tudo
    curl_easy_cleanup(curl_handle);
 return (0);
 
}
