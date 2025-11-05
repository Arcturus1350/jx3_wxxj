@echo off
chcp 65001 >nul
echo 开始处理data文件夹中的所有.in文件...
echo.

for %%f in (data\*.in) do (
    echo 正在处理: %%f
    std.exe < "%%f" > "%%~dpnf.out"
    echo 已生成: %%~dpnf.out
    echo.
)

echo.
echo 所有文件处理完成！
pause

