#!/bin/bash
# 增强版锁屏脚本：锁屏后熄屏，若屏幕被唤醒但10秒内未解锁，则再次熄屏

# 启动 slock 锁屏
slock &

# 等待3秒，确保 slock 已启动
sleep 3

# 检查 slock 进程是否存在
if ! pgrep -x "slock" > /dev/null; then
    echo "锁屏已提前解除，取消熄屏"
    exit 0
fi

# 首次强制熄屏
xset dpms force off

echo "屏幕已关闭，等待唤醒..."

# 主循环：检测屏幕状态和 slock 进程
while pgrep -x "slock" > /dev/null; do
    # 检查屏幕是否被唤醒（Monitor is On）
    if xset -q | grep -q "Monitor is On"; then
        echo "屏幕已唤醒，等待10秒解锁..."
        # 等待10秒
        sleep 10
        
        # 再次检查 slock 是否仍在运行
        if pgrep -x "slock" > /dev/null; then
            echo "10秒内未解锁，再次熄屏"
            xset dpms force off
            echo "屏幕已关闭，等待唤醒..."
        else
            echo "已解锁，退出脚本"
            exit 0
        fi
    fi
    
    # 短暂休眠以减少 CPU 占用
    sleep 1
done

echo "锁屏已解除，脚本结束"
