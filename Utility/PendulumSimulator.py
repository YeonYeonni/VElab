import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from matplotlib.widgets import TextBox, Button

L = 1.0  # 줄 길이 (그림용)

# ===== 기본값 =====
theta_max = np.deg2rad(90.0)   # 앞/뒤 최대 각도
dt = 0.001
T_total = 20.0
frame_skip = 10  # 10 프레임마다 1번 표시 (실시간 재생을 위해)

# 전역 변수
g = 0.0           # 중력 가속도 (m/s²)
omega_const = np.pi  # 초기 각속도(rad/s)
ani = None

# ===== Figure / Axes 세팅 =====
fig, ax = plt.subplots()
plt.subplots_adjust(bottom=0.25)

ax.set_aspect('equal', 'box')
ax.set_xlim(-1.2, 1.2)
ax.set_ylim(-1.2, 0.2)
ax.set_title("Pendulum Simulator")

line, = ax.plot([], [], lw=2)
bob, = ax.plot([], [], 'o', markersize=10)
info_text = ax.text(0.05, 0.95, "", transform=ax.transAxes,
                    va='top', ha='left')

# ===== UI 영역 =====
# 중력 가속도 입력 박스
axbox_g = plt.axes([0.1, 0.13, 0.35, 0.05])
text_box_g = TextBox(axbox_g, "g (m/s²): ", initial="0.0")

# 초기 각속도 입력 박스
axbox_omega = plt.axes([0.1, 0.06, 0.35, 0.05])
text_box_omega = TextBox(axbox_omega, "ω (rad/s): ", initial="pi")

# Run 버튼
axbutton_run = plt.axes([0.55, 0.13, 0.10, 0.05])
button_run = Button(axbutton_run, "Run")

# Stop 버튼
axbutton_stop = plt.axes([0.66, 0.13, 0.10, 0.05])
button_stop = Button(axbutton_stop, "Stop")

# Reset 버튼
axbutton_reset = plt.axes([0.55, 0.06, 0.10, 0.05])
button_reset = Button(axbutton_reset, "Reset")


def init():
    line.set_data([], [])
    bob.set_data([], [])
    info_text.set_text("")
    return line, bob, info_text


def update(frame):
    global theta, omega
    
    # 실제 데이터 인덱스 계산
    idx = frame * frame_skip
    if idx >= len(theta):
        idx = len(theta) - 1
    
    th = theta[idx]
    x = L * np.sin(th) # 진자의 x 좌표
    y = -L * np.cos(th) # 진자의 y 좌표

    line.set_data([0, x], [0, y])
    bob.set_data([x], [y])

    th_deg = np.rad2deg(th) # 진자의 각도(도)
    w = omega[idx] # 진자 각속도(rad/s)
    t = idx * dt  # 현재 시간
    info_text.set_text(f"time = {t:6.3f} s\ntheta = {th_deg:6.2f} deg\nomega = {w:7.3f} rad/s\ng = {g:.2f} m/s²")

    return line, bob, info_text


def parse_value(text):
    """입력 문자열을 파싱 (pi, 2*pi 등 지원)"""
    text = text.strip().lower()
    text = text.replace('pi', 'np.pi') # pi를 np.pi로 치환
    try:
        value = eval(text, {"__builtins__": None}, {"np": np}) # eval로 계산 (np.pi, 2*np.pi 등 지원)
        return float(value)
    except:
        raise ValueError("올바른 숫자 또는 pi 표현식을 입력하세요")


def start_animation(event):
    """Run 버튼 눌렀을 때"""
    global ani, g, omega_const, theta, omega, n_steps
    
    # 입력값 읽기
    text_g = text_box_g.text
    text_omega = text_box_omega.text
    
    try:
        g = parse_value(text_g)
        omega_const = parse_value(text_omega)
    except Exception as e:
        info_text.set_text(str(e))
        return
    
    if g < 0:
        info_text.set_text("g는 0 이상이어야 합니다.")
        return
    
    print(f"[시작] g = {g:.2f} m/s², omega = {omega_const:.3f} rad/s")
    
    # 시뮬레이션 계산
    n_steps = int(T_total / dt) # 시간 스텝 계수
    
    theta = np.zeros(n_steps) # θ(t_k)
    omega = np.zeros(n_steps) # w(t_k) = dθ/dt
    
    # 초기 조건
    theta[0] = 0.0
    omega[0] = omega_const # 사용자가 입력한 진자 초기 각속도
    
    # ===== 등속 회전 또는 진자 운동 =====
    for i in range(1, n_steps):
        
        if g > 0:
            # 각가속도 = -(g/L) * sin(theta)
            alpha = -(g / L) * np.sin(theta[i-1])
            # 각속도 업데이트 (중력 가속도가 있을 때)
            omega[i] = omega[i-1] + alpha * dt
            
            # 각도 업데이트
            theta[i] = theta[i-1] + omega[i] * dt
            
        else:
            # 현재 시간 스텝의 각도 = 이전 시간 스텝의 각도 + 이전 시간 스텝의 각속도 * 시간 간격
            theta[i] = theta[i-1] + omega[i-1] * dt
            
            # 경계(±theta_max)에서 방향 반전
            if theta[i] > theta_max:
                over = theta[i] - theta_max
                theta[i] = theta_max - over
                omega[i] = -omega[i-1]
            elif theta[i] < -theta_max:
                over = -theta_max - theta[i]
                theta[i] = -theta_max + over
                omega[i] = -omega[i-1]
            else:
                omega[i] = omega[i-1]
    
    # 이전 애니메이션 정지
    if ani is not None and getattr(ani, "event_source", None) is not None:
        ani.event_source.stop()
    
    # 새 애니메이션 시작 (프레임 스킵 적용)
    display_frames = n_steps // frame_skip
    display_interval = dt * frame_skip * 1000  # 실제 시간과 동기화
    ani_new = FuncAnimation(fig, update, frames=display_frames, init_func=init, interval=display_interval, blit=True, repeat=True)
    
    ani = ani_new
    fig.canvas.draw_idle()

def stop_animation(event):
    """Stop 버튼 눌렀을 때"""
    global ani
    
    if ani is not None and getattr(ani, "event_source", None) is not None:
        ani.event_source.stop()
    
    line.set_data([], [])
    bob.set_data([], [])
    info_text.set_text("")
    
    fig.canvas.draw_idle()
    print("[정지] 시뮬레이션 중지")


def reset_values(event):
    """Reset 버튼 눌렀을 때"""
    text_box_g.set_val("9.81")
    text_box_omega.set_val("pi")
    print("[리셋] g = 9.81 m/s², ω = π rad/s")


# 버튼 클릭 이벤트 연결
button_run.on_clicked(start_animation)
button_stop.on_clicked(stop_animation)
button_reset.on_clicked(reset_values)

plt.show()