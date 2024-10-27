# Combine partial archives
cat vendor/qcom/sdclang/compiler/bin/clang-19* > vendor/qcom/sdclang/compiler/bin/clang-19
cat vendor/qcom/sdclang/compiler/bin/clang-repl* > vendor/qcom/sdclang/compiler/bin/clang-repl
cat vendor/qcom/sdclang/compiler/bin/flang-new* > vendor/qcom/sdclang/compiler/bin/flang-new

# Make binaries from partial archive executable
chmod a+x vendor/qcom/sdclang/compiler/bin/clang-19
chmod a+x vendor/qcom/sdclang/compiler/bin/clang-repl
chmod a+x vendor/qcom/sdclang/compiler/bin/flang-new
