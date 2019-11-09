#!/bin/bash
RFC_NAME=rfc69420

echo "Getting RFC as text format"
curl -X POST https://xml2rfc.tools.ietf.org/cgi-bin/xml2rfc.cgi -F 'input=@./rfc.xml' -o $RFC_NAME
echo "Getting RFC as HTML format"
curl -X POST https://xml2rfc.tools.ietf.org/cgi-bin/xml2rfc.cgi -F 'input=@./rfc.xml' -F 'modeAsFormat=html/ascii' -o $RFC_NAME.html

if [ -s rfc69420 ]
then
  exit 0
else
  rm $RFC_NAME $RFC_NAME.html
  exit 1
fi
