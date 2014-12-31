set -e
valgrind ./json_parse 2>&1 | grep -q "ERROR SUMMARY: 0 errors from 0 contexts" || (echo "valgrind check failed" && exit 1)
./json_parse > _out.json
diff good_out.json _out.json
rm _*
echo "Success"
