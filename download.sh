#i/usr/bin/env bash

EXEC_FILE=./url_downloader
LOG_FILE=./assets/download.log
URL_FILE=./assets/download.url
TARGET_IMAGE=/var/www/html/wiki/data/media/pasted/mainpage.png
if [ ! -f ${EXEC_FILE} ]; then
    echo "$(date +%Y-%m-%d_%H:%M:%S) Error: can not find ${EXEC_FILE}" >> ${LOG_FILE}
    exit 1
fi

${EXEC_FILE} 0
if [ $? -ne 0 ]; then
    echo "$(date +%Y-%m-%d_%H:%M:%S) Error: execute ${EXEC_FILE} failed!" >> ${LOG_FILE}
    exit 1
fi
echo "$(date +%Y-%m-%d_%H:%M:%S) Info: execute ${EXEC_FILE} successfully!" >> ${LOG_FILE}

if [ ! -f ${URL_FILE} ]; then
    echo "$(date +%Y-%m-%d_%H:%M:%S) Error: can not find ${URL_FILE}" >> ${LOG_FILE}
    exit 1
fi
URL=$(sed -n '1p' ${URL_FILE})
echo ${URL}
wget ${URL} -O ${TARGET_IMAGE}
