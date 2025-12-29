import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from matplotlib.widgets import TextBox, Button

# ===== 물리 파라미터 =====
m1 = 1.0      # 첫 번째 진자의 질량 m1
m2 = 1.0      # 두 번째 진자의 질량 m2
L1 = 1.0      # 첫 번째 막대 길이 L1
L2 = 1.0      # 두 번째 막대 길이 L2

# ===== 기본값 =====
dt = 0.001    # 시간 간격 Δt [s]
T_total = 5.0  # 전체 시뮬레이션 시간 [s]
frame_skip = 10  # 10 프레임마다 1번 표시 (실시간 재생을 위해)

# 전역 변수
g = 9.81       # 중력 가속도 g (기본 9.81)
omega_const = np.pi  # 첫 번째 진자의 초기 각속도 ω1(0)(rad/s)
ani = None

# 시뮬레이션 상태 (이중 진자)
theta1 = None
omega1 = None
theta2 = None
omega2 = None
n_steps = None

# 궤적 추적용
trail_x = []
trail_y = []

# ===== Figure / Axes 세팅 =====
fig, ax = plt.subplots()
plt.subplots_adjust(bottom=0.25)

ax.set_aspect('equal', 'box')
# 두 막대 길이 합이 2.0이므로 대략 -2.2 ~ 2.2 정도로 잡음
axis_limit = (L1 + L2) * 1.2
ax.set_xlim(-axis_limit, axis_limit)
ax.set_ylim(-axis_limit, axis_limit)
ax.set_title("Dual Pendulum Simulator")

# 막대(두 개 연결) & 질점 두 개
line, = ax.plot([], [], lw=2)
bob1, = ax.plot([], [], 'o', markersize=8)
bob2, = ax.plot([], [], 'o', markersize=8)

# 궤적 선
trail, = ax.plot([], [], 'r-', lw=0.5, alpha=0.6)

info_text = ax.text(0.05, 0.95, "", transform=ax.transAxes,
                    va='top', ha='left')

# ===== UI 영역 =====
# 중력 가속도 입력 박스
axbox_g = plt.axes([0.1, 0.13, 0.35, 0.05])
text_box_g = TextBox(axbox_g, "g (m/s²): ", initial="9.81")

# 초기 각속도 입력 박스 (첫 번째 진자 ω1(0))
axbox_omega = plt.axes([0.1, 0.06, 0.35, 0.05])
text_box_omega = TextBox(axbox_omega, "ω1(0) (rad/s): ", initial="pi")

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
    global trail_x, trail_y
    line.set_data([], [])
    bob1.set_data([], [])
    bob2.set_data([], [])
    trail.set_data([], [])
    trail_x = []
    trail_y = []
    info_text.set_text("")
    return line, bob1, bob2, trail, info_text


def update(frame):
    global theta1, omega1, theta2, omega2, trail_x, trail_y

    # 실제 데이터 인덱스 계산
    idx = frame * frame_skip
    if idx >= len(theta1):
        idx = len(theta1) - 1

    th1 = theta1[idx]
    th2 = theta2[idx]

    # 첫 번째 진자 끝 위치
    x1 = L1 * np.sin(th1) # 첫 번째 질량의 x 좌표
    y1 = -L1 * np.cos(th1) # 첫 번째 질량의 y 좌표

    # 두 번째 진자 끝 위치
    x2 = x1 + L2 * np.sin(th2) # 두 번째 질량의 x 좌표
    y2 = y1 - L2 * np.cos(th2) # 두 번째 질량의 y 좌표

    # 막대 두 개를 하나의 라인으로 그림 (원점 -> bob1 -> bob2)
    line.set_data([0, x1, x2], [0, y1, y2])

    # 질점 위치
    bob1.set_data([x1], [y1])
    bob2.set_data([x2], [y2])

    # 두 번째 질량 좌표 궤적
    trail_x.append(x2)
    trail_y.append(y2)
    
    trail.set_data(trail_x, trail_y)

    # 텍스트 정보
    t = idx * dt # 현재 시간
    th1_deg = np.rad2deg(th1) # 첫 번째 진자 각도(도)
    th2_deg = np.rad2deg(th2) # 두 번째 진자 각도(도)
    w1 = omega1[idx] # 첫 번째 진자 각속도(rad/s)
    w2 = omega2[idx] # 두 번째 진자 각속도(rad/s)

    info_text.set_text(
        f"time = {t:6.3f} s\n"
        f"theta1 = {th1_deg:7.2f} deg\n"
        f"theta2 = {th2_deg:7.2f} deg\n"
        f"omega1 = {w1:8.3f} rad/s\n"
        f"omega2 = {w2:8.3f} rad/s\n"
        f"g = {g:.2f} m/s²\n"
        f"trail points = {len(trail_x)}"
    )

    return line, bob1, bob2, trail, info_text


def parse_value(text):
    """입력 문자열을 파싱 (pi, 2*pi 등 지원)"""
    text = text.strip().lower()
    text = text.replace('pi', 'np.pi')
    try:
        value = eval(text, {"__builtins__": None}, {"np": np})
        return float(value)
    except Exception:
        raise ValueError("올바른 숫자 또는 pi 표현식을 입력하세요")


def start_animation(event):
    """Run 버튼 눌렀을 때"""
    global ani, g, omega_const, theta1, omega1, theta2, omega2, n_steps

    # 입력값 읽기
    text_g = text_box_g.text
    text_omega = text_box_omega.text

    try:
        g = parse_value(text_g)
        omega_const = parse_value(text_omega)
    except Exception as e:
        info_text.set_text(str(e))
        return

    if g <= 0:
        info_text.set_text("g는 0 이상이어야 합니다.")
        return

    print(f"[시작] g = {g:.2f} m/s², omega1(0) = {omega_const:.3f} rad/s")

    # 시뮬레이션 계산
    n_steps = int(T_total / dt) # 시간 스텝 계수

    theta1 = np.zeros(n_steps)  # θ1(t_k)
    omega1 = np.zeros(n_steps)  # ω1(t_k) = dθ1/dt
    theta2 = np.zeros(n_steps)  # θ2(t_k)
    omega2 = np.zeros(n_steps)  # ω2(t_k)

    # 초기 조건
    # 예시: 둘 다 90도 근처에서 시작, 두 번째를 아주 조금 다르게 해서 chaotic behavior 관찰
    #theta1[0] = np.pi / 2         # 90도
    #theta2[0] = np.pi / 2 + 0.01  # 90도 + 아주 작은 offset
    theta1[0] = 0.0
    theta2[0] = 0.0
    
    omega1[0] = omega_const       # 사용자가 입력한 첫 번째 진자 초기 각속도
    omega2[0] = 0.0               # 두 번째 진자 초기 각속도는 0으로

    # ===== 이중 진자 운동 방정식 =====
    for i in range(1, n_steps):
        th1 = theta1[i-1]   # 현재 스텝의 θ1
        th2 = theta2[i-1]   # 현재 스텝의 θ2
        w1  = omega1[i-1]   # 현재 스텝의 ω1
        w2  = omega2[i-1]   # 현재 스텝의 ω2

        delta = th1 - th2 # 상대 각도 (Δ = θ1 - θ2)

        denom = 2 * m1 + m2 - m2 * np.cos(2 * th1 - 2 * th2) # 관성 항. 두 방정식을 풀었을 때 등장하는 공통 분모. 행렬식의 M(q)의 det와 관련한 스칼라

        ## 각가속도 (표준 double pendulum 공식)
        # 첫 번째 진자 각가속도
        domega1_dt = (
            - 2 * m2 * np.sin(delta) * (L2 * w2**2 + L1 * w1**2 * np.cos(delta)) # [속도]
            - (2 * m1 + m2) * g * np.sin(th1) - m2 * g * np.sin(th1 - 2 * th2) # [중력]
            ) / (L1 * denom)  # [관성]

        # 두 번째 진자 각가속도
        domega2_dt = (
            2 * np.sin(delta) * (L1 * w1**2 * (m1 + m2) + L2 * w2**2 * m2 * np.cos(delta) # [속도]
            + g * (m1 + m2) * np.cos(th1)) # [중력]
            ) / (L2 * denom)  # [관성]

        ## 적분: 시간에 따라 변하는 상태(각도, 각속도)를 미분방정식으로부터 한 스텝씩 누적해서 계산
        # 각속도 적분 (누적) 업데이트
        omega1[i] = w1 + domega1_dt * dt # ω1(t+Δt) = ω1(t) + ω̇1 Δt
        omega2[i] = w2 + domega2_dt * dt # ω2(t+Δt) = ω2(t) + ω̇2 Δt

        # 각도 적분 (누적) 업데이트
        theta1[i] = th1 + omega1[i] * dt # θ1(t+Δt) = θ1(t) + ω1(t+Δt) Δt
        theta2[i] = th2 + omega2[i] * dt # θ2(t+Δt) = θ2(t) + ω2(t+Δt) Δt

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
    bob1.set_data([], [])
    bob2.set_data([], [])
    info_text.set_text(f"[정지] 궤적 점 개수: {len(trail_x)}")

    fig.canvas.draw_idle()
    print(f"[정지] 시뮬레이션 중지, 궤적 점: {len(trail_x)}")


def reset_values(event):
    """Reset 버튼 눌렀을 때"""
    text_box_g.set_val("9.81")
    text_box_omega.set_val("0.0")
    print("[리셋] g = 9.81 m/s², omega1(0) = 0.0 rad/s")


# 버튼 클릭 이벤트 연결
button_run.on_clicked(start_animation)
button_stop.on_clicked(stop_animation)
button_reset.on_clicked(reset_values)

plt.show()