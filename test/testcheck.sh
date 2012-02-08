TOPDIR="../../.."
SCHEMA="${TOPDIR}/schema/sbol.xsd"
BINARY="${TOPDIR}/DIST/check"
FAILURES=0

echo "these should be valid:"
for valid_doc in ${TOPDIR}/examples/valid*.xml
do
    ./${BINARY} ${SCHEMA} ${valid_doc}
    if [ $? != 0 ]
    then
        echo "failed to verify ${valid_doc}"
        FAILURES=$((${FAILURES} + 1))
    fi
done

echo "and these should be invalid:"
for invalid_doc in ${TOPDIR}/examples/invalid*.xml
do
    ./${BINARY} ${SCHEMA} ${invalid_doc}
    if [ $? != 1 ]
    then
        echo "missed a problem in ${invalid_doc}"
        FAILURES=FAILURES=$((${FAILURES} + 1))
    fi
done

if [ ${FAILURES} == 0 ]
then
    echo "handled all the examples correctly"
else
    echo "misjudged ${FAILURES} examples"
fi
