#pragma once

struct user_cmd {

    char _pad0[ 0x4 ];
    int m_command_number;
    int m_tick_count;
    q_angle m_view_angles;
    vector_3d m_aim_direction;
    float m_forward_move;
    float m_side_move;
    float m_up_move;
    int	m_buttons;
    int	m_impulse;
    int	m_weapon_select;
    int	m_weapon_sub_type;
    int	m_random_seed;
    short m_moused_x;
    short m_moused_y;
    bool m_has_been_predicted;

};