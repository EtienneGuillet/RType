#!/bin/bash
RFC_NAME=rfc69420

echo "Getting RFC as text format"
curl -X POST https://xml2rfc.tools.ietf.org/cgi-bin/xml2rfc.cgi -F 'input=@./docs/rfc.xml' -o docs/$RFC_NAME
echo "Getting RFC as HTML format"
curl -X POST https://xml2rfc.tools.ietf.org/cgi-bin/xml2rfc.cgi -F 'input=@./docs/rfc.xml' -F 'modeAsFormat=html/ascii' -o docs/$RFC_NAME.html

if [ -s docs/$RFC_NAME ]
then
  exit 0
else
  rm docs/$RFC_NAME docs/$RFC_NAME.html
  exit 1
fi
