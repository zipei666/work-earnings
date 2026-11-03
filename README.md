# 上班赚钱器

Windows 10/11 64 位桌面程序，无需安装 Python 或其他运行环境。打开 `dist/WorkEarnings.exe` 即可使用。

## 预设

- 月薪：4500 元；每日净工作时间：7.5 小时；每周日休息。
- 上班：09:00；午休：12:00–13:00；下班：17:30。
- 点击右上角「设置」可修改工资、工时、上班时间、午休及每周休息日（0 为周日，1 为周一，依次至 6 为周六）。下班时间自动计算。
- 使用 Windows 本地日期与时间，跨日、跨月自动更新；无需保持程序打开。

## 心愿目标与新版界面

主界面采用收入卡片、心愿卡片和工时进度区。设置使用统一字体和星期下拉框。

点击「设置心愿」，填写物品名称及价格（0.01～1,000,000 元），即可查看已赚金额、完成百分比、剩余金额和预计赚够的日期与时间。

- 心愿收入从首次保存这一刻开始，关掉程序后仍会按排班估算。
- 自动跳过午休和每周休息日；跨月按新月份的工作日数量计算时薪。
- 更换心愿名称或价格会重新开始；内容不变则保留开始时间。
- 修改工资或作息会按新设置重新计算；不记录历史工资变动。
- 这是「赚到物品价格」的估算，不是储蓄余额，不扣除生活开支。
- 支持未来 100 年内的估计；超出范围会提示。

## 计算方式

本月日薪 = 月薪 ÷ 本月工作日数量（排除所设的每周休息日）。时薪 = 日薪 ÷ 每日净工时。今日已赚按当日班次已过的净工时实时计算，午休不增长，上班前为零，下班后封顶。

本月累计 = 本月过去工作日按满勤计算的收入 + 今日已赚。它是排班估算，不记录实际考勤，不包含节假日、请假、加班、奖金、税费或社保计算，不代表实发工资。改变设置会立即重算估计值。仅支持不跨午夜的班次。

设置保存在 `%APPDATA%\WorkEarnings\settings.ini`。程序不联网、不收集数据。

## 源码编译

Windows 安装 MinGW-w64 并将 gcc 加入 PATH，双击 `build.bat`。Linux 使用 MinGW-w64：

```sh
(cd src && x86_64-w64-mingw32-windres app.rc -o ../dist/app-resource.o)
x86_64-w64-mingw32-gcc -O2 -Wall -Wextra -Werror -municode -mwindows -static -s src/main.c dist/app-resource.o -o dist/WorkEarnings.exe -lgdi32 -luser32
gcc -Wall -Wextra -Werror tests/test_pay.c -o /tmp/test_pay -lm
/tmp/test_pay
gcc -Wall -Wextra -Werror tests/test_goal.c -o /tmp/test_goal -lm
/tmp/test_goal
```

已在 Linux 交叉编译生成 Windows x64 PE，验证仅依赖 Windows 系统 DLL，29 项收入与心愿计算检查通过。当前环境未运行 Windows 图形界面，仍需在 Windows 上确认窗口显示与设置保存。可执行文件未做代码签名。
