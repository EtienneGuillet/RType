#!/bin/bash
RFC_NAME=rfc69420

curl -X POST https://xml2rfc.tools.ietf.org/cgi-bin/xml2rfc.cgi -F 'input=@./rfc.xml' -o $RFC_NAME
curl -X POST https://xml2rfc.tools.ietf.org/cgi-bin/xml2rfc.cgi -F 'input=@./rfc.xml' -F 'modeAsFormat=html/ascii' -o $RFC_NAME.html