/* Include files */

#include <stddef.h>
#include "blas.h"
#include "WEC_Sim_Driver_sfun.h"
#include "c17_WEC_Sim_Driver.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "WEC_Sim_Driver_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c17_debug_family_names[35] = { "a", "b", "c", "axisRotx",
  "axisRoty", "dZ", "angleRotx", "angleRoty", "i", "j", "q", "costhetay",
  "sinthetay", "costhetax", "sinthetax", "x_m", "y_m", "z_m", "r_m", "r_a",
  "r_b", "r_c", "AB", "AC", "CP", "area", "PanelMoment", "nargin", "nargout",
  "STL", "Disp", "BodyForce", "BodyMoment", "TotalArea", "PanelForce" };

/* Function Declarations */
static void initialize_c17_WEC_Sim_Driver(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void initialize_params_c17_WEC_Sim_Driver
  (SFc17_WEC_Sim_DriverInstanceStruct *chartInstance);
static void enable_c17_WEC_Sim_Driver(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void disable_c17_WEC_Sim_Driver(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void c17_update_debugger_state_c17_WEC_Sim_Driver
  (SFc17_WEC_Sim_DriverInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c17_WEC_Sim_Driver
  (SFc17_WEC_Sim_DriverInstanceStruct *chartInstance);
static void set_sim_state_c17_WEC_Sim_Driver(SFc17_WEC_Sim_DriverInstanceStruct *
  chartInstance, const mxArray *c17_st);
static void finalize_c17_WEC_Sim_Driver(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void sf_c17_WEC_Sim_Driver(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void c17_chartstep_c17_WEC_Sim_Driver(SFc17_WEC_Sim_DriverInstanceStruct *
  chartInstance);
static void initSimStructsc17_WEC_Sim_Driver(SFc17_WEC_Sim_DriverInstanceStruct *
  chartInstance);
static void registerMessagesc17_WEC_Sim_Driver
  (SFc17_WEC_Sim_DriverInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c17_machineNumber, uint32_T
  c17_chartNumber);
static const mxArray *c17_sf_marshallOut(void *chartInstanceVoid, void
  *c17_inData);
static void c17_emlrt_marshallIn(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c17_PanelForce, const char_T *c17_identifier,
  real_T c17_y[3]);
static void c17_b_emlrt_marshallIn(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c17_u, const emlrtMsgIdentifier *c17_parentId,
  real_T c17_y[3]);
static void c17_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c17_mxArrayInData, const char_T *c17_varName, void *c17_outData);
static const mxArray *c17_b_sf_marshallOut(void *chartInstanceVoid, void
  *c17_inData);
static const mxArray *c17_c_sf_marshallOut(void *chartInstanceVoid, void
  *c17_inData);
static const mxArray *c17_d_sf_marshallOut(void *chartInstanceVoid, void
  *c17_inData);
static real_T c17_c_emlrt_marshallIn(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c17_u, const emlrtMsgIdentifier *c17_parentId);
static void c17_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c17_mxArrayInData, const char_T *c17_varName, void *c17_outData);
static const mxArray *c17_e_sf_marshallOut(void *chartInstanceVoid, void
  *c17_inData);
static void c17_d_emlrt_marshallIn(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c17_u, const emlrtMsgIdentifier *c17_parentId,
  real_T c17_y[3]);
static void c17_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c17_mxArrayInData, const char_T *c17_varName, void *c17_outData);
static void c17_cross(SFc17_WEC_Sim_DriverInstanceStruct *chartInstance, real_T
                      c17_a[3], real_T c17_b[3], real_T c17_c[3]);
static const mxArray *c17_f_sf_marshallOut(void *chartInstanceVoid, void
  *c17_inData);
static int32_T c17_e_emlrt_marshallIn(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c17_u, const emlrtMsgIdentifier *c17_parentId);
static void c17_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c17_mxArrayInData, const char_T *c17_varName, void *c17_outData);
static uint8_T c17_f_emlrt_marshallIn(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c17_b_is_active_c17_WEC_Sim_Driver, const
  char_T *c17_identifier);
static uint8_T c17_g_emlrt_marshallIn(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c17_u, const emlrtMsgIdentifier *c17_parentId);
static void init_dsm_address_info(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c17_WEC_Sim_Driver(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
  chartInstance->c17_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c17_is_active_c17_WEC_Sim_Driver = 0U;
}

static void initialize_params_c17_WEC_Sim_Driver
  (SFc17_WEC_Sim_DriverInstanceStruct *chartInstance)
{
}

static void enable_c17_WEC_Sim_Driver(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c17_WEC_Sim_Driver(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c17_update_debugger_state_c17_WEC_Sim_Driver
  (SFc17_WEC_Sim_DriverInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c17_WEC_Sim_Driver
  (SFc17_WEC_Sim_DriverInstanceStruct *chartInstance)
{
  const mxArray *c17_st;
  const mxArray *c17_y = NULL;
  int32_T c17_i0;
  real_T c17_u[3];
  const mxArray *c17_b_y = NULL;
  int32_T c17_i1;
  real_T c17_b_u[3];
  const mxArray *c17_c_y = NULL;
  int32_T c17_i2;
  real_T c17_c_u[3];
  const mxArray *c17_d_y = NULL;
  int32_T c17_i3;
  real_T c17_d_u[3];
  const mxArray *c17_e_y = NULL;
  uint8_T c17_hoistedGlobal;
  uint8_T c17_e_u;
  const mxArray *c17_f_y = NULL;
  real_T (*c17_TotalArea)[3];
  real_T (*c17_PanelForce)[3];
  real_T (*c17_BodyMoment)[3];
  real_T (*c17_BodyForce)[3];
  c17_PanelForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
  c17_TotalArea = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 3);
  c17_BodyMoment = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c17_BodyForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c17_st = NULL;
  c17_st = NULL;
  c17_y = NULL;
  sf_mex_assign(&c17_y, sf_mex_createcellarray(5), FALSE);
  for (c17_i0 = 0; c17_i0 < 3; c17_i0++) {
    c17_u[c17_i0] = (*c17_BodyForce)[c17_i0];
  }

  c17_b_y = NULL;
  sf_mex_assign(&c17_b_y, sf_mex_create("y", c17_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c17_y, 0, c17_b_y);
  for (c17_i1 = 0; c17_i1 < 3; c17_i1++) {
    c17_b_u[c17_i1] = (*c17_BodyMoment)[c17_i1];
  }

  c17_c_y = NULL;
  sf_mex_assign(&c17_c_y, sf_mex_create("y", c17_b_u, 0, 0U, 1U, 0U, 1, 3),
                FALSE);
  sf_mex_setcell(c17_y, 1, c17_c_y);
  for (c17_i2 = 0; c17_i2 < 3; c17_i2++) {
    c17_c_u[c17_i2] = (*c17_PanelForce)[c17_i2];
  }

  c17_d_y = NULL;
  sf_mex_assign(&c17_d_y, sf_mex_create("y", c17_c_u, 0, 0U, 1U, 0U, 1, 3),
                FALSE);
  sf_mex_setcell(c17_y, 2, c17_d_y);
  for (c17_i3 = 0; c17_i3 < 3; c17_i3++) {
    c17_d_u[c17_i3] = (*c17_TotalArea)[c17_i3];
  }

  c17_e_y = NULL;
  sf_mex_assign(&c17_e_y, sf_mex_create("y", c17_d_u, 0, 0U, 1U, 0U, 1, 3),
                FALSE);
  sf_mex_setcell(c17_y, 3, c17_e_y);
  c17_hoistedGlobal = chartInstance->c17_is_active_c17_WEC_Sim_Driver;
  c17_e_u = c17_hoistedGlobal;
  c17_f_y = NULL;
  sf_mex_assign(&c17_f_y, sf_mex_create("y", &c17_e_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c17_y, 4, c17_f_y);
  sf_mex_assign(&c17_st, c17_y, FALSE);
  return c17_st;
}

static void set_sim_state_c17_WEC_Sim_Driver(SFc17_WEC_Sim_DriverInstanceStruct *
  chartInstance, const mxArray *c17_st)
{
  const mxArray *c17_u;
  real_T c17_dv0[3];
  int32_T c17_i4;
  real_T c17_dv1[3];
  int32_T c17_i5;
  real_T c17_dv2[3];
  int32_T c17_i6;
  real_T c17_dv3[3];
  int32_T c17_i7;
  real_T (*c17_BodyForce)[3];
  real_T (*c17_BodyMoment)[3];
  real_T (*c17_PanelForce)[3];
  real_T (*c17_TotalArea)[3];
  c17_PanelForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
  c17_TotalArea = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 3);
  c17_BodyMoment = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c17_BodyForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c17_doneDoubleBufferReInit = TRUE;
  c17_u = sf_mex_dup(c17_st);
  c17_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c17_u, 0)),
                       "BodyForce", c17_dv0);
  for (c17_i4 = 0; c17_i4 < 3; c17_i4++) {
    (*c17_BodyForce)[c17_i4] = c17_dv0[c17_i4];
  }

  c17_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c17_u, 1)),
                       "BodyMoment", c17_dv1);
  for (c17_i5 = 0; c17_i5 < 3; c17_i5++) {
    (*c17_BodyMoment)[c17_i5] = c17_dv1[c17_i5];
  }

  c17_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c17_u, 2)),
                       "PanelForce", c17_dv2);
  for (c17_i6 = 0; c17_i6 < 3; c17_i6++) {
    (*c17_PanelForce)[c17_i6] = c17_dv2[c17_i6];
  }

  c17_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c17_u, 3)),
                       "TotalArea", c17_dv3);
  for (c17_i7 = 0; c17_i7 < 3; c17_i7++) {
    (*c17_TotalArea)[c17_i7] = c17_dv3[c17_i7];
  }

  chartInstance->c17_is_active_c17_WEC_Sim_Driver = c17_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c17_u, 4)),
     "is_active_c17_WEC_Sim_Driver");
  sf_mex_destroy(&c17_u);
  c17_update_debugger_state_c17_WEC_Sim_Driver(chartInstance);
  sf_mex_destroy(&c17_st);
}

static void finalize_c17_WEC_Sim_Driver(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
}

static void sf_c17_WEC_Sim_Driver(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
  int32_T c17_i8;
  int32_T c17_i9;
  int32_T c17_i10;
  int32_T c17_i11;
  int32_T c17_i12;
  int32_T c17_i13;
  real_T (*c17_PanelForce)[3];
  real_T (*c17_TotalArea)[3];
  real_T (*c17_BodyMoment)[3];
  real_T (*c17_Disp)[6];
  real_T (*c17_BodyForce)[3];
  real_T (*c17_STL)[9846];
  c17_PanelForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
  c17_TotalArea = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 3);
  c17_BodyMoment = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c17_Disp = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 1);
  c17_BodyForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c17_STL = (real_T (*)[9846])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 10U, chartInstance->c17_sfEvent);
  for (c17_i8 = 0; c17_i8 < 9846; c17_i8++) {
    _SFD_DATA_RANGE_CHECK((*c17_STL)[c17_i8], 0U);
  }

  for (c17_i9 = 0; c17_i9 < 3; c17_i9++) {
    _SFD_DATA_RANGE_CHECK((*c17_BodyForce)[c17_i9], 1U);
  }

  for (c17_i10 = 0; c17_i10 < 6; c17_i10++) {
    _SFD_DATA_RANGE_CHECK((*c17_Disp)[c17_i10], 2U);
  }

  for (c17_i11 = 0; c17_i11 < 3; c17_i11++) {
    _SFD_DATA_RANGE_CHECK((*c17_BodyMoment)[c17_i11], 3U);
  }

  for (c17_i12 = 0; c17_i12 < 3; c17_i12++) {
    _SFD_DATA_RANGE_CHECK((*c17_TotalArea)[c17_i12], 4U);
  }

  for (c17_i13 = 0; c17_i13 < 3; c17_i13++) {
    _SFD_DATA_RANGE_CHECK((*c17_PanelForce)[c17_i13], 5U);
  }

  chartInstance->c17_sfEvent = CALL_EVENT;
  c17_chartstep_c17_WEC_Sim_Driver(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_WEC_Sim_DriverMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c17_chartstep_c17_WEC_Sim_Driver(SFc17_WEC_Sim_DriverInstanceStruct *
  chartInstance)
{
  int32_T c17_i14;
  real_T c17_STL[9846];
  int32_T c17_i15;
  real_T c17_Disp[6];
  uint32_T c17_debug_family_var_map[35];
  real_T c17_a;
  real_T c17_b;
  real_T c17_c;
  real_T c17_axisRotx[3];
  real_T c17_axisRoty[3];
  real_T c17_dZ;
  real_T c17_angleRotx;
  real_T c17_angleRoty;
  real_T c17_i;
  real_T c17_j;
  real_T c17_q[3];
  real_T c17_costhetay;
  real_T c17_sinthetay;
  real_T c17_costhetax;
  real_T c17_sinthetax;
  real_T c17_x_m;
  real_T c17_y_m;
  real_T c17_z_m;
  real_T c17_r_m[3];
  real_T c17_r_a[3];
  real_T c17_r_b[3];
  real_T c17_r_c[3];
  real_T c17_AB[3];
  real_T c17_AC[3];
  real_T c17_CP[3];
  real_T c17_area[3];
  real_T c17_PanelMoment[3];
  real_T c17_nargin = 2.0;
  real_T c17_nargout = 4.0;
  real_T c17_BodyForce[3];
  real_T c17_BodyMoment[3];
  real_T c17_TotalArea[3];
  real_T c17_PanelForce[3];
  int32_T c17_i16;
  static real_T c17_dv4[3] = { 1.0, 0.0, 0.0 };

  int32_T c17_i17;
  static real_T c17_dv5[3] = { 0.0, 1.0, 0.0 };

  int32_T c17_b_i;
  int32_T c17_b_j;
  int32_T c17_i18;
  real_T c17_x;
  real_T c17_b_x;
  real_T c17_c_x;
  real_T c17_d_x;
  real_T c17_b_a;
  real_T c17_y;
  real_T c17_c_a;
  real_T c17_b_y;
  real_T c17_d_a;
  real_T c17_b_b;
  real_T c17_c_y;
  real_T c17_e_a;
  real_T c17_d_y;
  real_T c17_f_a;
  real_T c17_e_y;
  real_T c17_c_b;
  real_T c17_f_y;
  real_T c17_g_a;
  real_T c17_d_b;
  real_T c17_g_y;
  real_T c17_h_a;
  real_T c17_h_y;
  real_T c17_i_a;
  real_T c17_i_y;
  real_T c17_e_b;
  real_T c17_j_y;
  real_T c17_j_a;
  real_T c17_f_b;
  real_T c17_k_y;
  real_T c17_k_a;
  real_T c17_l_y;
  real_T c17_l_a;
  real_T c17_m_y;
  real_T c17_g_b;
  real_T c17_n_y;
  real_T c17_m_a;
  real_T c17_h_b;
  real_T c17_o_y;
  real_T c17_n_a;
  real_T c17_p_y;
  real_T c17_o_a;
  real_T c17_q_y;
  real_T c17_p_a;
  real_T c17_i_b;
  real_T c17_r_y;
  real_T c17_q_a;
  real_T c17_s_y;
  real_T c17_s_a;
  real_T c17_t_y;
  real_T c17_j_b;
  real_T c17_u_y;
  real_T c17_t_a;
  real_T c17_k_b;
  real_T c17_v_y;
  real_T c17_u_a;
  real_T c17_w_y;
  real_T c17_v_a;
  real_T c17_x_y;
  real_T c17_l_b;
  real_T c17_y_y;
  real_T c17_w_a;
  real_T c17_m_b;
  real_T c17_ab_y;
  real_T c17_x_a;
  real_T c17_bb_y;
  real_T c17_y_a;
  real_T c17_cb_y;
  real_T c17_n_b;
  real_T c17_db_y;
  real_T c17_ab_a;
  real_T c17_o_b;
  real_T c17_eb_y;
  real_T c17_bb_a;
  real_T c17_fb_y;
  real_T c17_cb_a;
  real_T c17_gb_y;
  real_T c17_db_a;
  real_T c17_p_b;
  real_T c17_hb_y;
  int32_T c17_c_j;
  int32_T c17_c_i;
  int32_T c17_i19;
  int32_T c17_d_i;
  int32_T c17_d_j;
  int32_T c17_i20;
  real_T c17_e_x;
  real_T c17_f_x;
  real_T c17_g_x;
  real_T c17_h_x;
  real_T c17_eb_a;
  real_T c17_ib_y;
  real_T c17_fb_a;
  real_T c17_jb_y;
  real_T c17_gb_a;
  real_T c17_q_b;
  real_T c17_kb_y;
  real_T c17_hb_a;
  real_T c17_lb_y;
  real_T c17_ib_a;
  real_T c17_mb_y;
  real_T c17_s_b;
  real_T c17_nb_y;
  real_T c17_jb_a;
  real_T c17_t_b;
  real_T c17_ob_y;
  real_T c17_kb_a;
  real_T c17_pb_y;
  real_T c17_lb_a;
  real_T c17_qb_y;
  real_T c17_u_b;
  real_T c17_rb_y;
  real_T c17_mb_a;
  real_T c17_v_b;
  real_T c17_sb_y;
  real_T c17_nb_a;
  real_T c17_tb_y;
  real_T c17_ob_a;
  real_T c17_ub_y;
  real_T c17_w_b;
  real_T c17_vb_y;
  real_T c17_pb_a;
  real_T c17_x_b;
  real_T c17_wb_y;
  real_T c17_qb_a;
  real_T c17_xb_y;
  real_T c17_rb_a;
  real_T c17_yb_y;
  real_T c17_sb_a;
  real_T c17_y_b;
  real_T c17_ac_y;
  real_T c17_tb_a;
  real_T c17_bc_y;
  real_T c17_ub_a;
  real_T c17_cc_y;
  real_T c17_ab_b;
  real_T c17_dc_y;
  real_T c17_vb_a;
  real_T c17_bb_b;
  real_T c17_ec_y;
  real_T c17_wb_a;
  real_T c17_fc_y;
  real_T c17_xb_a;
  real_T c17_gc_y;
  real_T c17_cb_b;
  real_T c17_hc_y;
  real_T c17_yb_a;
  real_T c17_db_b;
  real_T c17_ic_y;
  real_T c17_ac_a;
  real_T c17_jc_y;
  real_T c17_bc_a;
  real_T c17_kc_y;
  real_T c17_eb_b;
  real_T c17_lc_y;
  real_T c17_cc_a;
  real_T c17_fb_b;
  real_T c17_mc_y;
  real_T c17_dc_a;
  real_T c17_nc_y;
  real_T c17_ec_a;
  real_T c17_oc_y;
  real_T c17_fc_a;
  real_T c17_gb_b;
  real_T c17_pc_y;
  int32_T c17_e_j;
  int32_T c17_e_i;
  int32_T c17_i21;
  int32_T c17_i22;
  int32_T c17_i23;
  int32_T c17_i24;
  int32_T c17_f_i;
  real_T c17_A;
  real_T c17_i_x;
  real_T c17_j_x;
  real_T c17_b_A;
  real_T c17_k_x;
  real_T c17_l_x;
  real_T c17_c_A;
  real_T c17_m_x;
  real_T c17_n_x;
  int32_T c17_i25;
  int32_T c17_i26;
  int32_T c17_i27;
  real_T c17_b_AC[3];
  int32_T c17_i28;
  real_T c17_b_AB[3];
  real_T c17_dv6[3];
  int32_T c17_i29;
  int32_T c17_i30;
  real_T c17_hb_b[3];
  int32_T c17_i31;
  real_T c17_gc_a;
  int32_T c17_i32;
  int32_T c17_i33;
  int32_T c17_i34;
  int32_T c17_i35;
  real_T c17_b_r_m[3];
  int32_T c17_i36;
  real_T c17_b_PanelForce[3];
  real_T c17_dv7[3];
  int32_T c17_i37;
  int32_T c17_i38;
  int32_T c17_i39;
  int32_T c17_i40;
  int32_T c17_i41;
  int32_T c17_i42;
  int32_T c17_i43;
  real_T (*c17_b_BodyForce)[3];
  real_T (*c17_b_BodyMoment)[3];
  real_T (*c17_b_TotalArea)[3];
  real_T (*c17_c_PanelForce)[3];
  real_T (*c17_b_Disp)[6];
  real_T (*c17_b_STL)[9846];
  c17_c_PanelForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
  c17_b_TotalArea = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 3);
  c17_b_BodyMoment = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c17_b_Disp = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 1);
  c17_b_BodyForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c17_b_STL = (real_T (*)[9846])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 10U, chartInstance->c17_sfEvent);
  for (c17_i14 = 0; c17_i14 < 9846; c17_i14++) {
    c17_STL[c17_i14] = (*c17_b_STL)[c17_i14];
  }

  for (c17_i15 = 0; c17_i15 < 6; c17_i15++) {
    c17_Disp[c17_i15] = (*c17_b_Disp)[c17_i15];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 35U, 35U, c17_debug_family_names,
    c17_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c17_a, 0U, c17_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c17_b, 1U, c17_d_sf_marshallOut,
    c17_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c17_c, 2U, c17_d_sf_marshallOut,
    c17_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c17_axisRotx, 3U, c17_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c17_axisRoty, 4U, c17_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c17_dZ, 5U, c17_d_sf_marshallOut,
    c17_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c17_angleRotx, 6U, c17_d_sf_marshallOut,
    c17_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c17_angleRoty, 7U, c17_d_sf_marshallOut,
    c17_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c17_i, 8U, c17_d_sf_marshallOut,
    c17_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c17_j, 9U, c17_d_sf_marshallOut,
    c17_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c17_q, 10U, c17_e_sf_marshallOut,
    c17_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c17_costhetay, 11U, c17_d_sf_marshallOut,
    c17_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c17_sinthetay, 12U, c17_d_sf_marshallOut,
    c17_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c17_costhetax, 13U, c17_d_sf_marshallOut,
    c17_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c17_sinthetax, 14U, c17_d_sf_marshallOut,
    c17_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c17_x_m, 15U, c17_d_sf_marshallOut,
    c17_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c17_y_m, 16U, c17_d_sf_marshallOut,
    c17_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c17_z_m, 17U, c17_d_sf_marshallOut,
    c17_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c17_r_m, 18U, c17_sf_marshallOut,
    c17_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c17_r_a, 19U, c17_sf_marshallOut,
    c17_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c17_r_b, 20U, c17_sf_marshallOut,
    c17_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c17_r_c, 21U, c17_sf_marshallOut,
    c17_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c17_AB, 22U, c17_sf_marshallOut,
    c17_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c17_AC, 23U, c17_sf_marshallOut,
    c17_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c17_CP, 24U, c17_sf_marshallOut,
    c17_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c17_area, 25U, c17_sf_marshallOut,
    c17_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c17_PanelMoment, 26U, c17_sf_marshallOut,
    c17_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c17_nargin, 27U, c17_d_sf_marshallOut,
    c17_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c17_nargout, 28U, c17_d_sf_marshallOut,
    c17_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c17_STL, 29U, c17_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c17_Disp, 30U, c17_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c17_BodyForce, 31U, c17_sf_marshallOut,
    c17_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c17_BodyMoment, 32U, c17_sf_marshallOut,
    c17_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c17_TotalArea, 33U, c17_sf_marshallOut,
    c17_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c17_PanelForce, 34U, c17_sf_marshallOut,
    c17_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 15);
  c17_a = 1094.0;
  c17_b = 3.0;
  c17_c = 3.0;
  _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 20);
  for (c17_i16 = 0; c17_i16 < 3; c17_i16++) {
    c17_axisRotx[c17_i16] = c17_dv4[c17_i16];
  }

  _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 21);
  for (c17_i17 = 0; c17_i17 < 3; c17_i17++) {
    c17_axisRoty[c17_i17] = c17_dv5[c17_i17];
  }

  _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 22);
  c17_dZ = c17_Disp[2];
  _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 23);
  c17_angleRotx = c17_Disp[3];
  _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 24);
  c17_angleRoty = c17_Disp[4];
  _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 27);
  c17_i = 1.0;
  c17_b_i = 0;
  while (c17_b_i < 1094) {
    c17_i = 1.0 + (real_T)c17_b_i;
    CV_EML_FOR(0, 1, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 28);
    c17_j = 1.0;
    c17_b_j = 0;
    while (c17_b_j < 3) {
      c17_j = 1.0 + (real_T)c17_b_j;
      CV_EML_FOR(0, 1, 1, 1);
      _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 29);
      for (c17_i18 = 0; c17_i18 < 3; c17_i18++) {
        c17_q[c17_i18] = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 32);
      if (CV_EML_IF(0, 1, 0, c17_angleRoty != 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 34);
        c17_x = c17_angleRoty;
        c17_costhetay = c17_x;
        c17_b_x = c17_costhetay;
        c17_costhetay = c17_b_x;
        c17_costhetay = muDoubleScalarCos(c17_costhetay);
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 35);
        c17_c_x = c17_angleRoty;
        c17_sinthetay = c17_c_x;
        c17_d_x = c17_sinthetay;
        c17_sinthetay = c17_d_x;
        c17_sinthetay = muDoubleScalarSin(c17_sinthetay);
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 37);
        c17_b_a = 1.0 - c17_costhetay;
        c17_y = c17_b_a * 0.0;
        c17_c_a = c17_y;
        c17_b_y = c17_c_a * 0.0;
        c17_d_a = c17_costhetay + c17_b_y;
        c17_b_b = c17_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 1094 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c17_j), 1, 3, 2, 0)
                            - 1)) - 1];
        c17_c_y = c17_d_a * c17_b_b;
        c17_q[0] += c17_c_y;
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 38);
        c17_e_a = 1.0 - c17_costhetay;
        c17_d_y = c17_e_a * 0.0;
        c17_f_a = c17_d_y;
        c17_e_y = c17_f_a;
        c17_c_b = c17_sinthetay;
        c17_f_y = 0.0 * c17_c_b;
        c17_g_a = c17_e_y - c17_f_y;
        c17_d_b = c17_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 1094 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c17_j), 1, 3, 2, 0)
                            - 1)) + 3281];
        c17_g_y = c17_g_a * c17_d_b;
        c17_q[0] += c17_g_y;
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 39);
        c17_h_a = 1.0 - c17_costhetay;
        c17_h_y = c17_h_a * 0.0;
        c17_i_a = c17_h_y;
        c17_i_y = c17_i_a * 0.0;
        c17_e_b = c17_sinthetay;
        c17_j_y = c17_e_b;
        c17_j_a = c17_i_y + c17_j_y;
        c17_f_b = c17_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 1094 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c17_j), 1, 3, 2, 0)
                            - 1)) + 6563];
        c17_k_y = c17_j_a * c17_f_b;
        c17_q[0] += c17_k_y;
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 41);
        c17_k_a = 1.0 - c17_costhetay;
        c17_l_y = c17_k_a * 0.0;
        c17_l_a = c17_l_y;
        c17_m_y = c17_l_a;
        c17_g_b = c17_sinthetay;
        c17_n_y = 0.0 * c17_g_b;
        c17_m_a = c17_m_y + c17_n_y;
        c17_h_b = c17_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 1094 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c17_j), 1, 3, 2, 0)
                            - 1)) - 1];
        c17_o_y = c17_m_a * c17_h_b;
        c17_q[1] += c17_o_y;
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 42);
        c17_n_a = 1.0 - c17_costhetay;
        c17_p_y = c17_n_a;
        c17_o_a = c17_p_y;
        c17_q_y = c17_o_a;
        c17_p_a = c17_costhetay + c17_q_y;
        c17_i_b = c17_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 1094 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c17_j), 1, 3, 2, 0)
                            - 1)) + 3281];
        c17_r_y = c17_p_a * c17_i_b;
        c17_q[1] += c17_r_y;
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 43);
        c17_q_a = 1.0 - c17_costhetay;
        c17_s_y = c17_q_a;
        c17_s_a = c17_s_y;
        c17_t_y = c17_s_a * 0.0;
        c17_j_b = c17_sinthetay;
        c17_u_y = 0.0 * c17_j_b;
        c17_t_a = c17_t_y - c17_u_y;
        c17_k_b = c17_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 1094 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c17_j), 1, 3, 2, 0)
                            - 1)) + 6563];
        c17_v_y = c17_t_a * c17_k_b;
        c17_q[1] += c17_v_y;
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 45);
        c17_u_a = 1.0 - c17_costhetay;
        c17_w_y = c17_u_a * 0.0;
        c17_v_a = c17_w_y;
        c17_x_y = c17_v_a * 0.0;
        c17_l_b = c17_sinthetay;
        c17_y_y = c17_l_b;
        c17_w_a = c17_x_y - c17_y_y;
        c17_m_b = c17_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 1094 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c17_j), 1, 3, 2, 0)
                            - 1)) - 1];
        c17_ab_y = c17_w_a * c17_m_b;
        c17_q[2] += c17_ab_y;
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 46);
        c17_x_a = 1.0 - c17_costhetay;
        c17_bb_y = c17_x_a;
        c17_y_a = c17_bb_y;
        c17_cb_y = c17_y_a * 0.0;
        c17_n_b = c17_sinthetay;
        c17_db_y = 0.0 * c17_n_b;
        c17_ab_a = c17_cb_y + c17_db_y;
        c17_o_b = c17_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 1094 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c17_j), 1, 3, 2, 0)
                            - 1)) + 3281];
        c17_eb_y = c17_ab_a * c17_o_b;
        c17_q[2] += c17_eb_y;
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 47);
        c17_bb_a = 1.0 - c17_costhetay;
        c17_fb_y = c17_bb_a * 0.0;
        c17_cb_a = c17_fb_y;
        c17_gb_y = c17_cb_a * 0.0;
        c17_db_a = c17_costhetay + c17_gb_y;
        c17_p_b = c17_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 1094 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c17_j), 1, 3, 2, 0)
                            - 1)) + 6563];
        c17_hb_y = c17_db_a * c17_p_b;
        c17_q[2] += c17_hb_y;
      }

      _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 51);
      if (CV_EML_IF(0, 1, 1, c17_angleRoty != 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 53);
        c17_c_j = (int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL", (int32_T)
          _SFD_INTEGER_CHECK("j", c17_j), 1, 3, 2, 0) - 1;
        c17_c_i = (int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL", (int32_T)
          _SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) - 1;
        for (c17_i19 = 0; c17_i19 < 3; c17_i19++) {
          c17_STL[(c17_c_i + 1094 * c17_c_j) + 3282 * c17_i19] = c17_q[c17_i19];
        }
      }

      c17_b_j++;
      _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 1, 0);
    c17_b_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 0, 0);
  _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 58);
  c17_i = 1.0;
  c17_d_i = 0;
  while (c17_d_i < 1094) {
    c17_i = 1.0 + (real_T)c17_d_i;
    CV_EML_FOR(0, 1, 2, 1);
    _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 59);
    c17_j = 1.0;
    c17_d_j = 0;
    while (c17_d_j < 3) {
      c17_j = 1.0 + (real_T)c17_d_j;
      CV_EML_FOR(0, 1, 3, 1);
      _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 60);
      for (c17_i20 = 0; c17_i20 < 3; c17_i20++) {
        c17_q[c17_i20] = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 62);
      if (CV_EML_IF(0, 1, 2, c17_angleRotx != 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 64);
        c17_e_x = c17_angleRotx;
        c17_costhetax = c17_e_x;
        c17_f_x = c17_costhetax;
        c17_costhetax = c17_f_x;
        c17_costhetax = muDoubleScalarCos(c17_costhetax);
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 65);
        c17_g_x = c17_angleRotx;
        c17_sinthetax = c17_g_x;
        c17_h_x = c17_sinthetax;
        c17_sinthetax = c17_h_x;
        c17_sinthetax = muDoubleScalarSin(c17_sinthetax);
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 67);
        c17_eb_a = 1.0 - c17_costhetax;
        c17_ib_y = c17_eb_a;
        c17_fb_a = c17_ib_y;
        c17_jb_y = c17_fb_a;
        c17_gb_a = c17_costhetax + c17_jb_y;
        c17_q_b = c17_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 1094 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c17_j), 1, 3, 2, 0)
                            - 1)) - 1];
        c17_kb_y = c17_gb_a * c17_q_b;
        c17_q[0] += c17_kb_y;
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 68);
        c17_hb_a = 1.0 - c17_costhetax;
        c17_lb_y = c17_hb_a;
        c17_ib_a = c17_lb_y;
        c17_mb_y = c17_ib_a * 0.0;
        c17_s_b = c17_sinthetax;
        c17_nb_y = 0.0 * c17_s_b;
        c17_jb_a = c17_mb_y - c17_nb_y;
        c17_t_b = c17_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 1094 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c17_j), 1, 3, 2, 0)
                            - 1)) + 3281];
        c17_ob_y = c17_jb_a * c17_t_b;
        c17_q[0] += c17_ob_y;
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 69);
        c17_kb_a = 1.0 - c17_costhetax;
        c17_pb_y = c17_kb_a;
        c17_lb_a = c17_pb_y;
        c17_qb_y = c17_lb_a * 0.0;
        c17_u_b = c17_sinthetax;
        c17_rb_y = 0.0 * c17_u_b;
        c17_mb_a = c17_qb_y + c17_rb_y;
        c17_v_b = c17_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 1094 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c17_j), 1, 3, 2, 0)
                            - 1)) + 6563];
        c17_sb_y = c17_mb_a * c17_v_b;
        c17_q[0] += c17_sb_y;
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 71);
        c17_nb_a = 1.0 - c17_costhetax;
        c17_tb_y = c17_nb_a;
        c17_ob_a = c17_tb_y;
        c17_ub_y = c17_ob_a * 0.0;
        c17_w_b = c17_sinthetax;
        c17_vb_y = 0.0 * c17_w_b;
        c17_pb_a = c17_ub_y + c17_vb_y;
        c17_x_b = c17_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 1094 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c17_j), 1, 3, 2, 0)
                            - 1)) - 1];
        c17_wb_y = c17_pb_a * c17_x_b;
        c17_q[1] += c17_wb_y;
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 72);
        c17_qb_a = 1.0 - c17_costhetax;
        c17_xb_y = c17_qb_a * 0.0;
        c17_rb_a = c17_xb_y;
        c17_yb_y = c17_rb_a * 0.0;
        c17_sb_a = c17_costhetax + c17_yb_y;
        c17_y_b = c17_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 1094 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c17_j), 1, 3, 2, 0)
                            - 1)) + 3281];
        c17_ac_y = c17_sb_a * c17_y_b;
        c17_q[1] += c17_ac_y;
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 73);
        c17_tb_a = 1.0 - c17_costhetax;
        c17_bc_y = c17_tb_a * 0.0;
        c17_ub_a = c17_bc_y;
        c17_cc_y = c17_ub_a * 0.0;
        c17_ab_b = c17_sinthetax;
        c17_dc_y = c17_ab_b;
        c17_vb_a = c17_cc_y - c17_dc_y;
        c17_bb_b = c17_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1,
          0) + 1094 * ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("j", c17_j), 1, 3, 2, 0) - 1)) + 6563];
        c17_ec_y = c17_vb_a * c17_bb_b;
        c17_q[1] += c17_ec_y;
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 75);
        c17_wb_a = 1.0 - c17_costhetax;
        c17_fc_y = c17_wb_a;
        c17_xb_a = c17_fc_y;
        c17_gc_y = c17_xb_a * 0.0;
        c17_cb_b = c17_sinthetax;
        c17_hc_y = 0.0 * c17_cb_b;
        c17_yb_a = c17_gc_y - c17_hc_y;
        c17_db_b = c17_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1,
          0) + 1094 * ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("j", c17_j), 1, 3, 2, 0) - 1)) - 1];
        c17_ic_y = c17_yb_a * c17_db_b;
        c17_q[2] += c17_ic_y;
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 76);
        c17_ac_a = 1.0 - c17_costhetax;
        c17_jc_y = c17_ac_a * 0.0;
        c17_bc_a = c17_jc_y;
        c17_kc_y = c17_bc_a * 0.0;
        c17_eb_b = c17_sinthetax;
        c17_lc_y = c17_eb_b;
        c17_cc_a = c17_kc_y + c17_lc_y;
        c17_fb_b = c17_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1,
          0) + 1094 * ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("j", c17_j), 1, 3, 2, 0) - 1)) + 3281];
        c17_mc_y = c17_cc_a * c17_fb_b;
        c17_q[2] += c17_mc_y;
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 77);
        c17_dc_a = 1.0 - c17_costhetax;
        c17_nc_y = c17_dc_a * 0.0;
        c17_ec_a = c17_nc_y;
        c17_oc_y = c17_ec_a * 0.0;
        c17_fc_a = c17_costhetax + c17_oc_y;
        c17_gb_b = c17_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1,
          0) + 1094 * ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("j", c17_j), 1, 3, 2, 0) - 1)) + 6563];
        c17_pc_y = c17_fc_a * c17_gb_b;
        c17_q[2] += c17_pc_y;
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 79);
        c17_q[2] += c17_dZ;
      } else {
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 82);
        c17_q[0] = c17_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1,
          0) + 1094 * ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("j", c17_j), 1, 3, 2, 0) - 1)) - 1];
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 83);
        c17_q[1] = c17_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1,
          0) + 1094 * ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("j", c17_j), 1, 3, 2, 0) - 1)) + 3281];
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 84);
        c17_q[2] = c17_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1,
          0) + 1094 * ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("j", c17_j), 1, 3, 2, 0) - 1)) + 6563] +
          c17_dZ;
      }

      _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 88);
      if (CV_EML_IF(0, 1, 3, c17_q[2] > 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 89);
        c17_q[2] = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 93);
      c17_e_j = (int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL", (int32_T)
        _SFD_INTEGER_CHECK("j", c17_j), 1, 3, 2, 0) - 1;
      c17_e_i = (int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL", (int32_T)
        _SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) - 1;
      for (c17_i21 = 0; c17_i21 < 3; c17_i21++) {
        c17_STL[(c17_e_i + 1094 * c17_e_j) + 3282 * c17_i21] = c17_q[c17_i21];
      }

      c17_d_j++;
      _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 3, 0);
    c17_d_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 2, 0);
  _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 98);
  for (c17_i22 = 0; c17_i22 < 3; c17_i22++) {
    c17_BodyForce[c17_i22] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 99);
  for (c17_i23 = 0; c17_i23 < 3; c17_i23++) {
    c17_BodyMoment[c17_i23] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 100);
  for (c17_i24 = 0; c17_i24 < 3; c17_i24++) {
    c17_TotalArea[c17_i24] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 101);
  c17_i = 1.0;
  c17_f_i = 0;
  while (c17_f_i < 1094) {
    c17_i = 1.0 + (real_T)c17_f_i;
    CV_EML_FOR(0, 1, 4, 1);
    _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 102);
    c17_A = (c17_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
              (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) - 1] +
             c17_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
              (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 1093]) +
      c17_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL", (int32_T)
      _SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 2187];
    c17_i_x = c17_A;
    c17_j_x = c17_i_x;
    c17_x_m = c17_j_x / 3.0;
    _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 103);
    c17_b_A = (c17_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 3281]
               + c17_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 4375])
      + c17_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL", (int32_T)
      _SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 5469];
    c17_k_x = c17_b_A;
    c17_l_x = c17_k_x;
    c17_y_m = c17_l_x / 3.0;
    _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 104);
    c17_c_A = (c17_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 6563]
               + c17_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 7657])
      + c17_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL", (int32_T)
      _SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 8751];
    c17_m_x = c17_c_A;
    c17_n_x = c17_m_x;
    c17_z_m = c17_n_x / 3.0;
    _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 105);
    c17_r_m[0] = c17_x_m;
    c17_r_m[1] = c17_y_m;
    c17_r_m[2] = c17_z_m;
    _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 107);
    c17_r_a[0] = c17_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
      (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) - 1];
    c17_r_a[1] = c17_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
      (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 3281];
    c17_r_a[2] = c17_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
      (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 6563];
    _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 108);
    c17_r_b[0] = c17_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
      (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 1093];
    c17_r_b[1] = c17_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
      (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 4375];
    c17_r_b[2] = c17_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
      (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 7657];
    _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 109);
    c17_r_c[0] = c17_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
      (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 2187];
    c17_r_c[1] = c17_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
      (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 5469];
    c17_r_c[2] = c17_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
      (int32_T)_SFD_INTEGER_CHECK("i", c17_i), 1, 1094, 1, 0) + 8751];
    _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 111);
    for (c17_i25 = 0; c17_i25 < 3; c17_i25++) {
      c17_AB[c17_i25] = c17_r_b[c17_i25] - c17_r_a[c17_i25];
    }

    _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 112);
    for (c17_i26 = 0; c17_i26 < 3; c17_i26++) {
      c17_AC[c17_i26] = c17_r_c[c17_i26] - c17_r_a[c17_i26];
    }

    _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 113);
    for (c17_i27 = 0; c17_i27 < 3; c17_i27++) {
      c17_b_AC[c17_i27] = c17_AC[c17_i27];
    }

    for (c17_i28 = 0; c17_i28 < 3; c17_i28++) {
      c17_b_AB[c17_i28] = c17_AB[c17_i28];
    }

    c17_cross(chartInstance, c17_b_AC, c17_b_AB, c17_dv6);
    for (c17_i29 = 0; c17_i29 < 3; c17_i29++) {
      c17_CP[c17_i29] = c17_dv6[c17_i29];
    }

    _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 114);
    for (c17_i30 = 0; c17_i30 < 3; c17_i30++) {
      c17_hb_b[c17_i30] = c17_CP[c17_i30];
    }

    for (c17_i31 = 0; c17_i31 < 3; c17_i31++) {
      c17_area[c17_i31] = 0.5 * c17_hb_b[c17_i31];
    }

    _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 116);
    c17_gc_a = -c17_z_m;
    for (c17_i32 = 0; c17_i32 < 3; c17_i32++) {
      c17_hb_b[c17_i32] = c17_area[c17_i32];
    }

    for (c17_i33 = 0; c17_i33 < 3; c17_i33++) {
      c17_PanelForce[c17_i33] = c17_gc_a * c17_hb_b[c17_i33];
    }

    _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 117);
    for (c17_i34 = 0; c17_i34 < 3; c17_i34++) {
      c17_BodyForce[c17_i34] += c17_PanelForce[c17_i34];
    }

    _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 119);
    for (c17_i35 = 0; c17_i35 < 3; c17_i35++) {
      c17_b_r_m[c17_i35] = c17_r_m[c17_i35];
    }

    for (c17_i36 = 0; c17_i36 < 3; c17_i36++) {
      c17_b_PanelForce[c17_i36] = c17_PanelForce[c17_i36];
    }

    c17_cross(chartInstance, c17_b_r_m, c17_b_PanelForce, c17_dv7);
    for (c17_i37 = 0; c17_i37 < 3; c17_i37++) {
      c17_PanelMoment[c17_i37] = c17_dv7[c17_i37];
    }

    _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 120);
    for (c17_i38 = 0; c17_i38 < 3; c17_i38++) {
      c17_BodyMoment[c17_i38] += c17_PanelMoment[c17_i38];
    }

    _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, 121);
    for (c17_i39 = 0; c17_i39 < 3; c17_i39++) {
      c17_TotalArea[c17_i39] += c17_area[c17_i39];
    }

    c17_f_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 4, 0);
  _SFD_EML_CALL(0U, chartInstance->c17_sfEvent, -121);
  _SFD_SYMBOL_SCOPE_POP();
  for (c17_i40 = 0; c17_i40 < 3; c17_i40++) {
    (*c17_b_BodyForce)[c17_i40] = c17_BodyForce[c17_i40];
  }

  for (c17_i41 = 0; c17_i41 < 3; c17_i41++) {
    (*c17_b_BodyMoment)[c17_i41] = c17_BodyMoment[c17_i41];
  }

  for (c17_i42 = 0; c17_i42 < 3; c17_i42++) {
    (*c17_b_TotalArea)[c17_i42] = c17_TotalArea[c17_i42];
  }

  for (c17_i43 = 0; c17_i43 < 3; c17_i43++) {
    (*c17_c_PanelForce)[c17_i43] = c17_PanelForce[c17_i43];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 10U, chartInstance->c17_sfEvent);
}

static void initSimStructsc17_WEC_Sim_Driver(SFc17_WEC_Sim_DriverInstanceStruct *
  chartInstance)
{
}

static void registerMessagesc17_WEC_Sim_Driver
  (SFc17_WEC_Sim_DriverInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c17_machineNumber, uint32_T
  c17_chartNumber)
{
}

static const mxArray *c17_sf_marshallOut(void *chartInstanceVoid, void
  *c17_inData)
{
  const mxArray *c17_mxArrayOutData = NULL;
  int32_T c17_i44;
  real_T c17_b_inData[3];
  int32_T c17_i45;
  real_T c17_u[3];
  const mxArray *c17_y = NULL;
  SFc17_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc17_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c17_mxArrayOutData = NULL;
  for (c17_i44 = 0; c17_i44 < 3; c17_i44++) {
    c17_b_inData[c17_i44] = (*(real_T (*)[3])c17_inData)[c17_i44];
  }

  for (c17_i45 = 0; c17_i45 < 3; c17_i45++) {
    c17_u[c17_i45] = c17_b_inData[c17_i45];
  }

  c17_y = NULL;
  sf_mex_assign(&c17_y, sf_mex_create("y", c17_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c17_mxArrayOutData, c17_y, FALSE);
  return c17_mxArrayOutData;
}

static void c17_emlrt_marshallIn(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c17_PanelForce, const char_T *c17_identifier,
  real_T c17_y[3])
{
  emlrtMsgIdentifier c17_thisId;
  c17_thisId.fIdentifier = c17_identifier;
  c17_thisId.fParent = NULL;
  c17_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c17_PanelForce), &c17_thisId,
    c17_y);
  sf_mex_destroy(&c17_PanelForce);
}

static void c17_b_emlrt_marshallIn(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c17_u, const emlrtMsgIdentifier *c17_parentId,
  real_T c17_y[3])
{
  real_T c17_dv8[3];
  int32_T c17_i46;
  sf_mex_import(c17_parentId, sf_mex_dup(c17_u), c17_dv8, 1, 0, 0U, 1, 0U, 1, 3);
  for (c17_i46 = 0; c17_i46 < 3; c17_i46++) {
    c17_y[c17_i46] = c17_dv8[c17_i46];
  }

  sf_mex_destroy(&c17_u);
}

static void c17_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c17_mxArrayInData, const char_T *c17_varName, void *c17_outData)
{
  const mxArray *c17_PanelForce;
  const char_T *c17_identifier;
  emlrtMsgIdentifier c17_thisId;
  real_T c17_y[3];
  int32_T c17_i47;
  SFc17_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc17_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c17_PanelForce = sf_mex_dup(c17_mxArrayInData);
  c17_identifier = c17_varName;
  c17_thisId.fIdentifier = c17_identifier;
  c17_thisId.fParent = NULL;
  c17_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c17_PanelForce), &c17_thisId,
    c17_y);
  sf_mex_destroy(&c17_PanelForce);
  for (c17_i47 = 0; c17_i47 < 3; c17_i47++) {
    (*(real_T (*)[3])c17_outData)[c17_i47] = c17_y[c17_i47];
  }

  sf_mex_destroy(&c17_mxArrayInData);
}

static const mxArray *c17_b_sf_marshallOut(void *chartInstanceVoid, void
  *c17_inData)
{
  const mxArray *c17_mxArrayOutData = NULL;
  int32_T c17_i48;
  real_T c17_b_inData[6];
  int32_T c17_i49;
  real_T c17_u[6];
  const mxArray *c17_y = NULL;
  SFc17_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc17_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c17_mxArrayOutData = NULL;
  for (c17_i48 = 0; c17_i48 < 6; c17_i48++) {
    c17_b_inData[c17_i48] = (*(real_T (*)[6])c17_inData)[c17_i48];
  }

  for (c17_i49 = 0; c17_i49 < 6; c17_i49++) {
    c17_u[c17_i49] = c17_b_inData[c17_i49];
  }

  c17_y = NULL;
  sf_mex_assign(&c17_y, sf_mex_create("y", c17_u, 0, 0U, 1U, 0U, 1, 6), FALSE);
  sf_mex_assign(&c17_mxArrayOutData, c17_y, FALSE);
  return c17_mxArrayOutData;
}

static const mxArray *c17_c_sf_marshallOut(void *chartInstanceVoid, void
  *c17_inData)
{
  const mxArray *c17_mxArrayOutData = NULL;
  int32_T c17_i50;
  int32_T c17_i51;
  int32_T c17_i52;
  int32_T c17_i53;
  int32_T c17_i54;
  real_T c17_b_inData[9846];
  int32_T c17_i55;
  int32_T c17_i56;
  int32_T c17_i57;
  int32_T c17_i58;
  int32_T c17_i59;
  real_T c17_u[9846];
  const mxArray *c17_y = NULL;
  SFc17_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc17_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c17_mxArrayOutData = NULL;
  c17_i50 = 0;
  for (c17_i51 = 0; c17_i51 < 3; c17_i51++) {
    c17_i52 = 0;
    for (c17_i53 = 0; c17_i53 < 3; c17_i53++) {
      for (c17_i54 = 0; c17_i54 < 1094; c17_i54++) {
        c17_b_inData[(c17_i54 + c17_i52) + c17_i50] = (*(real_T (*)[9846])
          c17_inData)[(c17_i54 + c17_i52) + c17_i50];
      }

      c17_i52 += 1094;
    }

    c17_i50 += 3282;
  }

  c17_i55 = 0;
  for (c17_i56 = 0; c17_i56 < 3; c17_i56++) {
    c17_i57 = 0;
    for (c17_i58 = 0; c17_i58 < 3; c17_i58++) {
      for (c17_i59 = 0; c17_i59 < 1094; c17_i59++) {
        c17_u[(c17_i59 + c17_i57) + c17_i55] = c17_b_inData[(c17_i59 + c17_i57)
          + c17_i55];
      }

      c17_i57 += 1094;
    }

    c17_i55 += 3282;
  }

  c17_y = NULL;
  sf_mex_assign(&c17_y, sf_mex_create("y", c17_u, 0, 0U, 1U, 0U, 3, 1094, 3, 3),
                FALSE);
  sf_mex_assign(&c17_mxArrayOutData, c17_y, FALSE);
  return c17_mxArrayOutData;
}

static const mxArray *c17_d_sf_marshallOut(void *chartInstanceVoid, void
  *c17_inData)
{
  const mxArray *c17_mxArrayOutData = NULL;
  real_T c17_u;
  const mxArray *c17_y = NULL;
  SFc17_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc17_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c17_mxArrayOutData = NULL;
  c17_u = *(real_T *)c17_inData;
  c17_y = NULL;
  sf_mex_assign(&c17_y, sf_mex_create("y", &c17_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c17_mxArrayOutData, c17_y, FALSE);
  return c17_mxArrayOutData;
}

static real_T c17_c_emlrt_marshallIn(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c17_u, const emlrtMsgIdentifier *c17_parentId)
{
  real_T c17_y;
  real_T c17_d0;
  sf_mex_import(c17_parentId, sf_mex_dup(c17_u), &c17_d0, 1, 0, 0U, 0, 0U, 0);
  c17_y = c17_d0;
  sf_mex_destroy(&c17_u);
  return c17_y;
}

static void c17_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c17_mxArrayInData, const char_T *c17_varName, void *c17_outData)
{
  const mxArray *c17_nargout;
  const char_T *c17_identifier;
  emlrtMsgIdentifier c17_thisId;
  real_T c17_y;
  SFc17_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc17_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c17_nargout = sf_mex_dup(c17_mxArrayInData);
  c17_identifier = c17_varName;
  c17_thisId.fIdentifier = c17_identifier;
  c17_thisId.fParent = NULL;
  c17_y = c17_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c17_nargout),
    &c17_thisId);
  sf_mex_destroy(&c17_nargout);
  *(real_T *)c17_outData = c17_y;
  sf_mex_destroy(&c17_mxArrayInData);
}

static const mxArray *c17_e_sf_marshallOut(void *chartInstanceVoid, void
  *c17_inData)
{
  const mxArray *c17_mxArrayOutData = NULL;
  int32_T c17_i60;
  real_T c17_b_inData[3];
  int32_T c17_i61;
  real_T c17_u[3];
  const mxArray *c17_y = NULL;
  SFc17_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc17_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c17_mxArrayOutData = NULL;
  for (c17_i60 = 0; c17_i60 < 3; c17_i60++) {
    c17_b_inData[c17_i60] = (*(real_T (*)[3])c17_inData)[c17_i60];
  }

  for (c17_i61 = 0; c17_i61 < 3; c17_i61++) {
    c17_u[c17_i61] = c17_b_inData[c17_i61];
  }

  c17_y = NULL;
  sf_mex_assign(&c17_y, sf_mex_create("y", c17_u, 0, 0U, 1U, 0U, 2, 1, 3), FALSE);
  sf_mex_assign(&c17_mxArrayOutData, c17_y, FALSE);
  return c17_mxArrayOutData;
}

static void c17_d_emlrt_marshallIn(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c17_u, const emlrtMsgIdentifier *c17_parentId,
  real_T c17_y[3])
{
  real_T c17_dv9[3];
  int32_T c17_i62;
  sf_mex_import(c17_parentId, sf_mex_dup(c17_u), c17_dv9, 1, 0, 0U, 1, 0U, 2, 1,
                3);
  for (c17_i62 = 0; c17_i62 < 3; c17_i62++) {
    c17_y[c17_i62] = c17_dv9[c17_i62];
  }

  sf_mex_destroy(&c17_u);
}

static void c17_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c17_mxArrayInData, const char_T *c17_varName, void *c17_outData)
{
  const mxArray *c17_q;
  const char_T *c17_identifier;
  emlrtMsgIdentifier c17_thisId;
  real_T c17_y[3];
  int32_T c17_i63;
  SFc17_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc17_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c17_q = sf_mex_dup(c17_mxArrayInData);
  c17_identifier = c17_varName;
  c17_thisId.fIdentifier = c17_identifier;
  c17_thisId.fParent = NULL;
  c17_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c17_q), &c17_thisId, c17_y);
  sf_mex_destroy(&c17_q);
  for (c17_i63 = 0; c17_i63 < 3; c17_i63++) {
    (*(real_T (*)[3])c17_outData)[c17_i63] = c17_y[c17_i63];
  }

  sf_mex_destroy(&c17_mxArrayInData);
}

const mxArray *sf_c17_WEC_Sim_Driver_get_eml_resolved_functions_info(void)
{
  const mxArray *c17_nameCaptureInfo;
  c17_ResolvedFunctionInfo c17_info[11];
  c17_ResolvedFunctionInfo (*c17_b_info)[11];
  const mxArray *c17_m0 = NULL;
  int32_T c17_i64;
  c17_ResolvedFunctionInfo *c17_r0;
  c17_nameCaptureInfo = NULL;
  c17_nameCaptureInfo = NULL;
  c17_b_info = (c17_ResolvedFunctionInfo (*)[11])c17_info;
  (*c17_b_info)[0].context = "";
  (*c17_b_info)[0].name = "cos";
  (*c17_b_info)[0].dominantType = "double";
  (*c17_b_info)[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  (*c17_b_info)[0].fileTimeLo = 1343859172U;
  (*c17_b_info)[0].fileTimeHi = 0U;
  (*c17_b_info)[0].mFileTimeLo = 0U;
  (*c17_b_info)[0].mFileTimeHi = 0U;
  (*c17_b_info)[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  (*c17_b_info)[1].name = "eml_scalar_cos";
  (*c17_b_info)[1].dominantType = "double";
  (*c17_b_info)[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  (*c17_b_info)[1].fileTimeLo = 1286847522U;
  (*c17_b_info)[1].fileTimeHi = 0U;
  (*c17_b_info)[1].mFileTimeLo = 0U;
  (*c17_b_info)[1].mFileTimeHi = 0U;
  (*c17_b_info)[2].context = "";
  (*c17_b_info)[2].name = "sin";
  (*c17_b_info)[2].dominantType = "double";
  (*c17_b_info)[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  (*c17_b_info)[2].fileTimeLo = 1343859186U;
  (*c17_b_info)[2].fileTimeHi = 0U;
  (*c17_b_info)[2].mFileTimeLo = 0U;
  (*c17_b_info)[2].mFileTimeHi = 0U;
  (*c17_b_info)[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  (*c17_b_info)[3].name = "eml_scalar_sin";
  (*c17_b_info)[3].dominantType = "double";
  (*c17_b_info)[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  (*c17_b_info)[3].fileTimeLo = 1286847536U;
  (*c17_b_info)[3].fileTimeHi = 0U;
  (*c17_b_info)[3].mFileTimeLo = 0U;
  (*c17_b_info)[3].mFileTimeHi = 0U;
  (*c17_b_info)[4].context = "";
  (*c17_b_info)[4].name = "mtimes";
  (*c17_b_info)[4].dominantType = "double";
  (*c17_b_info)[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c17_b_info)[4].fileTimeLo = 1289548492U;
  (*c17_b_info)[4].fileTimeHi = 0U;
  (*c17_b_info)[4].mFileTimeLo = 0U;
  (*c17_b_info)[4].mFileTimeHi = 0U;
  (*c17_b_info)[5].context = "";
  (*c17_b_info)[5].name = "mrdivide";
  (*c17_b_info)[5].dominantType = "double";
  (*c17_b_info)[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  (*c17_b_info)[5].fileTimeLo = 1357980348U;
  (*c17_b_info)[5].fileTimeHi = 0U;
  (*c17_b_info)[5].mFileTimeLo = 1319758766U;
  (*c17_b_info)[5].mFileTimeHi = 0U;
  (*c17_b_info)[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  (*c17_b_info)[6].name = "rdivide";
  (*c17_b_info)[6].dominantType = "double";
  (*c17_b_info)[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c17_b_info)[6].fileTimeLo = 1346539188U;
  (*c17_b_info)[6].fileTimeHi = 0U;
  (*c17_b_info)[6].mFileTimeLo = 0U;
  (*c17_b_info)[6].mFileTimeHi = 0U;
  (*c17_b_info)[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c17_b_info)[7].name = "eml_scalexp_compatible";
  (*c17_b_info)[7].dominantType = "double";
  (*c17_b_info)[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  (*c17_b_info)[7].fileTimeLo = 1286847596U;
  (*c17_b_info)[7].fileTimeHi = 0U;
  (*c17_b_info)[7].mFileTimeLo = 0U;
  (*c17_b_info)[7].mFileTimeHi = 0U;
  (*c17_b_info)[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c17_b_info)[8].name = "eml_div";
  (*c17_b_info)[8].dominantType = "double";
  (*c17_b_info)[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  (*c17_b_info)[8].fileTimeLo = 1313376610U;
  (*c17_b_info)[8].fileTimeHi = 0U;
  (*c17_b_info)[8].mFileTimeLo = 0U;
  (*c17_b_info)[8].mFileTimeHi = 0U;
  (*c17_b_info)[9].context = "";
  (*c17_b_info)[9].name = "cross";
  (*c17_b_info)[9].dominantType = "double";
  (*c17_b_info)[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  (*c17_b_info)[9].fileTimeLo = 1286847642U;
  (*c17_b_info)[9].fileTimeHi = 0U;
  (*c17_b_info)[9].mFileTimeLo = 0U;
  (*c17_b_info)[9].mFileTimeHi = 0U;
  (*c17_b_info)[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  (*c17_b_info)[10].name = "mtimes";
  (*c17_b_info)[10].dominantType = "double";
  (*c17_b_info)[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c17_b_info)[10].fileTimeLo = 1289548492U;
  (*c17_b_info)[10].fileTimeHi = 0U;
  (*c17_b_info)[10].mFileTimeLo = 0U;
  (*c17_b_info)[10].mFileTimeHi = 0U;
  sf_mex_assign(&c17_m0, sf_mex_createstruct("nameCaptureInfo", 1, 11), FALSE);
  for (c17_i64 = 0; c17_i64 < 11; c17_i64++) {
    c17_r0 = &c17_info[c17_i64];
    sf_mex_addfield(c17_m0, sf_mex_create("nameCaptureInfo", c17_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c17_r0->context)), "context", "nameCaptureInfo",
                    c17_i64);
    sf_mex_addfield(c17_m0, sf_mex_create("nameCaptureInfo", c17_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c17_r0->name)), "name", "nameCaptureInfo",
                    c17_i64);
    sf_mex_addfield(c17_m0, sf_mex_create("nameCaptureInfo",
      c17_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c17_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c17_i64);
    sf_mex_addfield(c17_m0, sf_mex_create("nameCaptureInfo", c17_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c17_r0->resolved)), "resolved",
                    "nameCaptureInfo", c17_i64);
    sf_mex_addfield(c17_m0, sf_mex_create("nameCaptureInfo", &c17_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c17_i64);
    sf_mex_addfield(c17_m0, sf_mex_create("nameCaptureInfo", &c17_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c17_i64);
    sf_mex_addfield(c17_m0, sf_mex_create("nameCaptureInfo",
      &c17_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c17_i64);
    sf_mex_addfield(c17_m0, sf_mex_create("nameCaptureInfo",
      &c17_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c17_i64);
  }

  sf_mex_assign(&c17_nameCaptureInfo, c17_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c17_nameCaptureInfo);
  return c17_nameCaptureInfo;
}

static void c17_cross(SFc17_WEC_Sim_DriverInstanceStruct *chartInstance, real_T
                      c17_a[3], real_T c17_b[3], real_T c17_c[3])
{
  real_T c17_b_a;
  real_T c17_b_b;
  real_T c17_y;
  real_T c17_c_a;
  real_T c17_c_b;
  real_T c17_b_y;
  real_T c17_c1;
  real_T c17_d_a;
  real_T c17_d_b;
  real_T c17_c_y;
  real_T c17_e_a;
  real_T c17_e_b;
  real_T c17_d_y;
  real_T c17_c2;
  real_T c17_f_a;
  real_T c17_f_b;
  real_T c17_e_y;
  real_T c17_g_a;
  real_T c17_g_b;
  real_T c17_f_y;
  real_T c17_c3;
  c17_b_a = c17_a[1];
  c17_b_b = c17_b[2];
  c17_y = c17_b_a * c17_b_b;
  c17_c_a = c17_a[2];
  c17_c_b = c17_b[1];
  c17_b_y = c17_c_a * c17_c_b;
  c17_c1 = c17_y - c17_b_y;
  c17_d_a = c17_a[2];
  c17_d_b = c17_b[0];
  c17_c_y = c17_d_a * c17_d_b;
  c17_e_a = c17_a[0];
  c17_e_b = c17_b[2];
  c17_d_y = c17_e_a * c17_e_b;
  c17_c2 = c17_c_y - c17_d_y;
  c17_f_a = c17_a[0];
  c17_f_b = c17_b[1];
  c17_e_y = c17_f_a * c17_f_b;
  c17_g_a = c17_a[1];
  c17_g_b = c17_b[0];
  c17_f_y = c17_g_a * c17_g_b;
  c17_c3 = c17_e_y - c17_f_y;
  c17_c[0] = c17_c1;
  c17_c[1] = c17_c2;
  c17_c[2] = c17_c3;
}

static const mxArray *c17_f_sf_marshallOut(void *chartInstanceVoid, void
  *c17_inData)
{
  const mxArray *c17_mxArrayOutData = NULL;
  int32_T c17_u;
  const mxArray *c17_y = NULL;
  SFc17_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc17_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c17_mxArrayOutData = NULL;
  c17_u = *(int32_T *)c17_inData;
  c17_y = NULL;
  sf_mex_assign(&c17_y, sf_mex_create("y", &c17_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c17_mxArrayOutData, c17_y, FALSE);
  return c17_mxArrayOutData;
}

static int32_T c17_e_emlrt_marshallIn(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c17_u, const emlrtMsgIdentifier *c17_parentId)
{
  int32_T c17_y;
  int32_T c17_i65;
  sf_mex_import(c17_parentId, sf_mex_dup(c17_u), &c17_i65, 1, 6, 0U, 0, 0U, 0);
  c17_y = c17_i65;
  sf_mex_destroy(&c17_u);
  return c17_y;
}

static void c17_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c17_mxArrayInData, const char_T *c17_varName, void *c17_outData)
{
  const mxArray *c17_b_sfEvent;
  const char_T *c17_identifier;
  emlrtMsgIdentifier c17_thisId;
  int32_T c17_y;
  SFc17_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc17_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c17_b_sfEvent = sf_mex_dup(c17_mxArrayInData);
  c17_identifier = c17_varName;
  c17_thisId.fIdentifier = c17_identifier;
  c17_thisId.fParent = NULL;
  c17_y = c17_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c17_b_sfEvent),
    &c17_thisId);
  sf_mex_destroy(&c17_b_sfEvent);
  *(int32_T *)c17_outData = c17_y;
  sf_mex_destroy(&c17_mxArrayInData);
}

static uint8_T c17_f_emlrt_marshallIn(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c17_b_is_active_c17_WEC_Sim_Driver, const
  char_T *c17_identifier)
{
  uint8_T c17_y;
  emlrtMsgIdentifier c17_thisId;
  c17_thisId.fIdentifier = c17_identifier;
  c17_thisId.fParent = NULL;
  c17_y = c17_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c17_b_is_active_c17_WEC_Sim_Driver), &c17_thisId);
  sf_mex_destroy(&c17_b_is_active_c17_WEC_Sim_Driver);
  return c17_y;
}

static uint8_T c17_g_emlrt_marshallIn(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c17_u, const emlrtMsgIdentifier *c17_parentId)
{
  uint8_T c17_y;
  uint8_T c17_u0;
  sf_mex_import(c17_parentId, sf_mex_dup(c17_u), &c17_u0, 1, 3, 0U, 0, 0U, 0);
  c17_y = c17_u0;
  sf_mex_destroy(&c17_u);
  return c17_y;
}

static void init_dsm_address_info(SFc17_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c17_WEC_Sim_Driver_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3014316709U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3465963209U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2606685647U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3562214224U);
}

mxArray *sf_c17_WEC_Sim_Driver_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("upPhmEv7vhLE3NfYpZB1hG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,3,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1094);
      pr[1] = (double)(3);
      pr[2] = (double)(3);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c17_WEC_Sim_Driver_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c17_WEC_Sim_Driver(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[5],T\"BodyForce\",},{M[1],M[10],T\"BodyMoment\",},{M[1],M[14],T\"PanelForce\",},{M[1],M[13],T\"TotalArea\",},{M[8],M[0],T\"is_active_c17_WEC_Sim_Driver\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c17_WEC_Sim_Driver_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc17_WEC_Sim_DriverInstanceStruct *chartInstance;
    chartInstance = (SFc17_WEC_Sim_DriverInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _WEC_Sim_DriverMachineNumber_,
           17,
           1,
           1,
           6,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_WEC_Sim_DriverMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_WEC_Sim_DriverMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _WEC_Sim_DriverMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"STL");
          _SFD_SET_DATA_PROPS(1,2,0,1,"BodyForce");
          _SFD_SET_DATA_PROPS(2,1,1,0,"Disp");
          _SFD_SET_DATA_PROPS(3,2,0,1,"BodyMoment");
          _SFD_SET_DATA_PROPS(4,2,0,1,"TotalArea");
          _SFD_SET_DATA_PROPS(5,2,0,1,"PanelForce");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,4,0,0,0,5,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,5034);
        _SFD_CV_INIT_EML_IF(0,1,0,1110,1127,-1,2285);
        _SFD_CV_INIT_EML_IF(0,1,1,2294,2311,-1,2375);
        _SFD_CV_INIT_EML_IF(0,1,2,2489,2506,3659,3803);
        _SFD_CV_INIT_EML_IF(0,1,3,3856,3867,-1,3901);
        _SFD_CV_INIT_EML_FOR(0,1,0,1002,1014,2387);
        _SFD_CV_INIT_EML_FOR(0,1,1,1018,1030,2383);
        _SFD_CV_INIT_EML_FOR(0,1,2,2389,2401,3974);
        _SFD_CV_INIT_EML_FOR(0,1,3,2405,2417,3970);
        _SFD_CV_INIT_EML_FOR(0,1,4,4091,4103,4961);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[3];
          dimVector[0]= 1094;
          dimVector[1]= 3;
          dimVector[2]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,3,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c17_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c17_sf_marshallOut,(MexInFcnForType)
            c17_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c17_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c17_sf_marshallOut,(MexInFcnForType)
            c17_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c17_sf_marshallOut,(MexInFcnForType)
            c17_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c17_sf_marshallOut,(MexInFcnForType)
            c17_sf_marshallIn);
        }

        {
          real_T (*c17_STL)[9846];
          real_T (*c17_BodyForce)[3];
          real_T (*c17_Disp)[6];
          real_T (*c17_BodyMoment)[3];
          real_T (*c17_TotalArea)[3];
          real_T (*c17_PanelForce)[3];
          c17_PanelForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
            4);
          c17_TotalArea = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
            3);
          c17_BodyMoment = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
            2);
          c17_Disp = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 1);
          c17_BodyForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
            1);
          c17_STL = (real_T (*)[9846])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c17_STL);
          _SFD_SET_DATA_VALUE_PTR(1U, *c17_BodyForce);
          _SFD_SET_DATA_VALUE_PTR(2U, *c17_Disp);
          _SFD_SET_DATA_VALUE_PTR(3U, *c17_BodyMoment);
          _SFD_SET_DATA_VALUE_PTR(4U, *c17_TotalArea);
          _SFD_SET_DATA_VALUE_PTR(5U, *c17_PanelForce);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _WEC_Sim_DriverMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "7YVpEHvaGZ10MNiMVPWyEB";
}

static void sf_opaque_initialize_c17_WEC_Sim_Driver(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc17_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c17_WEC_Sim_Driver((SFc17_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar);
  initialize_c17_WEC_Sim_Driver((SFc17_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c17_WEC_Sim_Driver(void *chartInstanceVar)
{
  enable_c17_WEC_Sim_Driver((SFc17_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c17_WEC_Sim_Driver(void *chartInstanceVar)
{
  disable_c17_WEC_Sim_Driver((SFc17_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c17_WEC_Sim_Driver(void *chartInstanceVar)
{
  sf_c17_WEC_Sim_Driver((SFc17_WEC_Sim_DriverInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c17_WEC_Sim_Driver(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c17_WEC_Sim_Driver
    ((SFc17_WEC_Sim_DriverInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c17_WEC_Sim_Driver();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c17_WEC_Sim_Driver(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c17_WEC_Sim_Driver();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c17_WEC_Sim_Driver((SFc17_WEC_Sim_DriverInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c17_WEC_Sim_Driver(SimStruct* S)
{
  return sf_internal_get_sim_state_c17_WEC_Sim_Driver(S);
}

static void sf_opaque_set_sim_state_c17_WEC_Sim_Driver(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c17_WEC_Sim_Driver(S, st);
}

static void sf_opaque_terminate_c17_WEC_Sim_Driver(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc17_WEC_Sim_DriverInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_WEC_Sim_Driver_optimization_info();
    }

    finalize_c17_WEC_Sim_Driver((SFc17_WEC_Sim_DriverInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc17_WEC_Sim_Driver((SFc17_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c17_WEC_Sim_Driver(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c17_WEC_Sim_Driver((SFc17_WEC_Sim_DriverInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c17_WEC_Sim_Driver(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_WEC_Sim_Driver_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      17);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,17,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,17,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,17);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,17,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,17,4);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=4; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 2; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,17);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3611479375U));
  ssSetChecksum1(S,(2315835747U));
  ssSetChecksum2(S,(4068593548U));
  ssSetChecksum3(S,(608398705U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c17_WEC_Sim_Driver(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c17_WEC_Sim_Driver(SimStruct *S)
{
  SFc17_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc17_WEC_Sim_DriverInstanceStruct *)utMalloc(sizeof
    (SFc17_WEC_Sim_DriverInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc17_WEC_Sim_DriverInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c17_WEC_Sim_Driver;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c17_WEC_Sim_Driver;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c17_WEC_Sim_Driver;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c17_WEC_Sim_Driver;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c17_WEC_Sim_Driver;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c17_WEC_Sim_Driver;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c17_WEC_Sim_Driver;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c17_WEC_Sim_Driver;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c17_WEC_Sim_Driver;
  chartInstance->chartInfo.mdlStart = mdlStart_c17_WEC_Sim_Driver;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c17_WEC_Sim_Driver;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c17_WEC_Sim_Driver_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c17_WEC_Sim_Driver(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c17_WEC_Sim_Driver(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c17_WEC_Sim_Driver(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c17_WEC_Sim_Driver_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
