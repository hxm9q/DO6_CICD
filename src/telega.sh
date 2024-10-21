#!/bin/bash
TELEGRAM_BOT_TOKEN="7030399087:AAGYDUEn1tV8XB7kksxdSqV1UD11Fw-AOUk"
URL="https://api.telegram.org/bot$TELEGRAM_API_TOKEN/sendMessage"
CHAT_ID="-1002111027831"

URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
TEXT="Deploy status: $1%0A%0AProject:+$CI_PROJECT_NAME%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG
SUCCESS!  Проект выполнен на отлично!"

curl -s -d "chat_id=$CHAT_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null