#!/bin/sh

set -ev

echo $0

# This test ensures that strict will fail if we do not include in the
# facfile an input that is generated by another rule.

rm -rf $0.dir
mkdir $0.dir
cd $0.dir

cat > top.fac <<EOF
| cp facfile facfile.fac && echo good > good
> facfile.fac
EOF

cat > facfile <<EOF
| cp good excellent
< good
EOF

git init
git add top.fac facfile

${FAC:-../../fac} --strict

grep good good
grep good excellent

exit 0
