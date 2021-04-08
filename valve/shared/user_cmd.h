#pragma once

struct user_cmd {

    char _pad0[ 0x4 ]; // 0
    int m_command_number; // 4
    int m_tick_count; // 8
    q_angle m_view_angles; // 12
    vector_3d m_aim_direction; // 24
    float m_forward_move; // 36
    float m_side_move; // 40
    float m_up_move; // 44
    int	m_buttons; // 48
    int	m_impulse; // 52
    int	m_weapon_select; // 56
    int	m_weapon_sub_type; // 60
    int	m_random_seed; // 64
    short m_moused_x; // 68
    short m_moused_y; // 70
    bool m_has_been_predicted; // 72
    q_angle head_angles; // 73
    vector_3d head_offset; // 85

};