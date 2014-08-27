/* Include files */

#include <stddef.h>
#include "blas.h"
#include "WEC_Sim_Driver_sfun.h"
#include "c12_WEC_Sim_Driver.h"
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
static const char * c12_debug_family_names[35] = { "a", "b", "c", "axisRotx",
  "axisRoty", "dZ", "angleRotx", "angleRoty", "i", "j", "q", "costhetay",
  "sinthetay", "costhetax", "sinthetax", "x_m", "y_m", "z_m", "r_m", "r_a",
  "r_b", "r_c", "AB", "AC", "CP", "area", "PanelMoment", "nargin", "nargout",
  "STL", "Disp2", "BodyForce", "BodyMoment", "TotalArea", "PanelForce" };

/* Function Declarations */
static void initialize_c12_WEC_Sim_Driver(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void initialize_params_c12_WEC_Sim_Driver
  (SFc12_WEC_Sim_DriverInstanceStruct *chartInstance);
static void enable_c12_WEC_Sim_Driver(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void disable_c12_WEC_Sim_Driver(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void c12_update_debugger_state_c12_WEC_Sim_Driver
  (SFc12_WEC_Sim_DriverInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c12_WEC_Sim_Driver
  (SFc12_WEC_Sim_DriverInstanceStruct *chartInstance);
static void set_sim_state_c12_WEC_Sim_Driver(SFc12_WEC_Sim_DriverInstanceStruct *
  chartInstance, const mxArray *c12_st);
static void finalize_c12_WEC_Sim_Driver(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void sf_c12_WEC_Sim_Driver(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void c12_chartstep_c12_WEC_Sim_Driver(SFc12_WEC_Sim_DriverInstanceStruct *
  chartInstance);
static void initSimStructsc12_WEC_Sim_Driver(SFc12_WEC_Sim_DriverInstanceStruct *
  chartInstance);
static void registerMessagesc12_WEC_Sim_Driver
  (SFc12_WEC_Sim_DriverInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c12_machineNumber, uint32_T
  c12_chartNumber);
static const mxArray *c12_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static void c12_emlrt_marshallIn(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c12_PanelForce, const char_T *c12_identifier,
  real_T c12_y[3]);
static void c12_b_emlrt_marshallIn(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId,
  real_T c12_y[3]);
static void c12_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static const mxArray *c12_b_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static const mxArray *c12_c_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static const mxArray *c12_d_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static real_T c12_c_emlrt_marshallIn(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static void c12_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static const mxArray *c12_e_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static void c12_d_emlrt_marshallIn(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId,
  real_T c12_y[3]);
static void c12_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static void c12_cross(SFc12_WEC_Sim_DriverInstanceStruct *chartInstance, real_T
                      c12_a[3], real_T c12_b[3], real_T c12_c[3]);
static const mxArray *c12_f_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData);
static int32_T c12_e_emlrt_marshallIn(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static void c12_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData);
static uint8_T c12_f_emlrt_marshallIn(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c12_b_is_active_c12_WEC_Sim_Driver, const
  char_T *c12_identifier);
static uint8_T c12_g_emlrt_marshallIn(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId);
static void init_dsm_address_info(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c12_WEC_Sim_Driver(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
  chartInstance->c12_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c12_is_active_c12_WEC_Sim_Driver = 0U;
}

static void initialize_params_c12_WEC_Sim_Driver
  (SFc12_WEC_Sim_DriverInstanceStruct *chartInstance)
{
}

static void enable_c12_WEC_Sim_Driver(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c12_WEC_Sim_Driver(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c12_update_debugger_state_c12_WEC_Sim_Driver
  (SFc12_WEC_Sim_DriverInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c12_WEC_Sim_Driver
  (SFc12_WEC_Sim_DriverInstanceStruct *chartInstance)
{
  const mxArray *c12_st;
  const mxArray *c12_y = NULL;
  int32_T c12_i0;
  real_T c12_u[3];
  const mxArray *c12_b_y = NULL;
  int32_T c12_i1;
  real_T c12_b_u[3];
  const mxArray *c12_c_y = NULL;
  int32_T c12_i2;
  real_T c12_c_u[3];
  const mxArray *c12_d_y = NULL;
  int32_T c12_i3;
  real_T c12_d_u[3];
  const mxArray *c12_e_y = NULL;
  uint8_T c12_hoistedGlobal;
  uint8_T c12_e_u;
  const mxArray *c12_f_y = NULL;
  real_T (*c12_TotalArea)[3];
  real_T (*c12_PanelForce)[3];
  real_T (*c12_BodyMoment)[3];
  real_T (*c12_BodyForce)[3];
  c12_PanelForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
  c12_TotalArea = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 3);
  c12_BodyMoment = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c12_BodyForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c12_st = NULL;
  c12_st = NULL;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_createcellarray(5), FALSE);
  for (c12_i0 = 0; c12_i0 < 3; c12_i0++) {
    c12_u[c12_i0] = (*c12_BodyForce)[c12_i0];
  }

  c12_b_y = NULL;
  sf_mex_assign(&c12_b_y, sf_mex_create("y", c12_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c12_y, 0, c12_b_y);
  for (c12_i1 = 0; c12_i1 < 3; c12_i1++) {
    c12_b_u[c12_i1] = (*c12_BodyMoment)[c12_i1];
  }

  c12_c_y = NULL;
  sf_mex_assign(&c12_c_y, sf_mex_create("y", c12_b_u, 0, 0U, 1U, 0U, 1, 3),
                FALSE);
  sf_mex_setcell(c12_y, 1, c12_c_y);
  for (c12_i2 = 0; c12_i2 < 3; c12_i2++) {
    c12_c_u[c12_i2] = (*c12_PanelForce)[c12_i2];
  }

  c12_d_y = NULL;
  sf_mex_assign(&c12_d_y, sf_mex_create("y", c12_c_u, 0, 0U, 1U, 0U, 1, 3),
                FALSE);
  sf_mex_setcell(c12_y, 2, c12_d_y);
  for (c12_i3 = 0; c12_i3 < 3; c12_i3++) {
    c12_d_u[c12_i3] = (*c12_TotalArea)[c12_i3];
  }

  c12_e_y = NULL;
  sf_mex_assign(&c12_e_y, sf_mex_create("y", c12_d_u, 0, 0U, 1U, 0U, 1, 3),
                FALSE);
  sf_mex_setcell(c12_y, 3, c12_e_y);
  c12_hoistedGlobal = chartInstance->c12_is_active_c12_WEC_Sim_Driver;
  c12_e_u = c12_hoistedGlobal;
  c12_f_y = NULL;
  sf_mex_assign(&c12_f_y, sf_mex_create("y", &c12_e_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c12_y, 4, c12_f_y);
  sf_mex_assign(&c12_st, c12_y, FALSE);
  return c12_st;
}

static void set_sim_state_c12_WEC_Sim_Driver(SFc12_WEC_Sim_DriverInstanceStruct *
  chartInstance, const mxArray *c12_st)
{
  const mxArray *c12_u;
  real_T c12_dv0[3];
  int32_T c12_i4;
  real_T c12_dv1[3];
  int32_T c12_i5;
  real_T c12_dv2[3];
  int32_T c12_i6;
  real_T c12_dv3[3];
  int32_T c12_i7;
  real_T (*c12_BodyForce)[3];
  real_T (*c12_BodyMoment)[3];
  real_T (*c12_PanelForce)[3];
  real_T (*c12_TotalArea)[3];
  c12_PanelForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
  c12_TotalArea = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 3);
  c12_BodyMoment = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c12_BodyForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c12_doneDoubleBufferReInit = TRUE;
  c12_u = sf_mex_dup(c12_st);
  c12_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c12_u, 0)),
                       "BodyForce", c12_dv0);
  for (c12_i4 = 0; c12_i4 < 3; c12_i4++) {
    (*c12_BodyForce)[c12_i4] = c12_dv0[c12_i4];
  }

  c12_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c12_u, 1)),
                       "BodyMoment", c12_dv1);
  for (c12_i5 = 0; c12_i5 < 3; c12_i5++) {
    (*c12_BodyMoment)[c12_i5] = c12_dv1[c12_i5];
  }

  c12_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c12_u, 2)),
                       "PanelForce", c12_dv2);
  for (c12_i6 = 0; c12_i6 < 3; c12_i6++) {
    (*c12_PanelForce)[c12_i6] = c12_dv2[c12_i6];
  }

  c12_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c12_u, 3)),
                       "TotalArea", c12_dv3);
  for (c12_i7 = 0; c12_i7 < 3; c12_i7++) {
    (*c12_TotalArea)[c12_i7] = c12_dv3[c12_i7];
  }

  chartInstance->c12_is_active_c12_WEC_Sim_Driver = c12_f_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c12_u, 4)),
     "is_active_c12_WEC_Sim_Driver");
  sf_mex_destroy(&c12_u);
  c12_update_debugger_state_c12_WEC_Sim_Driver(chartInstance);
  sf_mex_destroy(&c12_st);
}

static void finalize_c12_WEC_Sim_Driver(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
}

static void sf_c12_WEC_Sim_Driver(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
  int32_T c12_i8;
  int32_T c12_i9;
  int32_T c12_i10;
  int32_T c12_i11;
  int32_T c12_i12;
  int32_T c12_i13;
  real_T (*c12_PanelForce)[3];
  real_T (*c12_TotalArea)[3];
  real_T (*c12_BodyMoment)[3];
  real_T (*c12_Disp2)[6];
  real_T (*c12_BodyForce)[3];
  real_T (*c12_STL)[23742];
  c12_PanelForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
  c12_TotalArea = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 3);
  c12_BodyMoment = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c12_Disp2 = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 1);
  c12_BodyForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c12_STL = (real_T (*)[23742])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 8U, chartInstance->c12_sfEvent);
  for (c12_i8 = 0; c12_i8 < 23742; c12_i8++) {
    _SFD_DATA_RANGE_CHECK((*c12_STL)[c12_i8], 0U);
  }

  for (c12_i9 = 0; c12_i9 < 3; c12_i9++) {
    _SFD_DATA_RANGE_CHECK((*c12_BodyForce)[c12_i9], 1U);
  }

  for (c12_i10 = 0; c12_i10 < 6; c12_i10++) {
    _SFD_DATA_RANGE_CHECK((*c12_Disp2)[c12_i10], 2U);
  }

  for (c12_i11 = 0; c12_i11 < 3; c12_i11++) {
    _SFD_DATA_RANGE_CHECK((*c12_BodyMoment)[c12_i11], 3U);
  }

  for (c12_i12 = 0; c12_i12 < 3; c12_i12++) {
    _SFD_DATA_RANGE_CHECK((*c12_TotalArea)[c12_i12], 4U);
  }

  for (c12_i13 = 0; c12_i13 < 3; c12_i13++) {
    _SFD_DATA_RANGE_CHECK((*c12_PanelForce)[c12_i13], 5U);
  }

  chartInstance->c12_sfEvent = CALL_EVENT;
  c12_chartstep_c12_WEC_Sim_Driver(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_WEC_Sim_DriverMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c12_chartstep_c12_WEC_Sim_Driver(SFc12_WEC_Sim_DriverInstanceStruct *
  chartInstance)
{
  int32_T c12_i14;
  real_T c12_STL[23742];
  int32_T c12_i15;
  real_T c12_Disp2[6];
  uint32_T c12_debug_family_var_map[35];
  real_T c12_a;
  real_T c12_b;
  real_T c12_c;
  real_T c12_axisRotx[3];
  real_T c12_axisRoty[3];
  real_T c12_dZ;
  real_T c12_angleRotx;
  real_T c12_angleRoty;
  real_T c12_i;
  real_T c12_j;
  real_T c12_q[3];
  real_T c12_costhetay;
  real_T c12_sinthetay;
  real_T c12_costhetax;
  real_T c12_sinthetax;
  real_T c12_x_m;
  real_T c12_y_m;
  real_T c12_z_m;
  real_T c12_r_m[3];
  real_T c12_r_a[3];
  real_T c12_r_b[3];
  real_T c12_r_c[3];
  real_T c12_AB[3];
  real_T c12_AC[3];
  real_T c12_CP[3];
  real_T c12_area[3];
  real_T c12_PanelMoment[3];
  real_T c12_nargin = 2.0;
  real_T c12_nargout = 4.0;
  real_T c12_BodyForce[3];
  real_T c12_BodyMoment[3];
  real_T c12_TotalArea[3];
  real_T c12_PanelForce[3];
  int32_T c12_i16;
  static real_T c12_dv4[3] = { 1.0, 0.0, 0.0 };

  int32_T c12_i17;
  static real_T c12_dv5[3] = { 0.0, 1.0, 0.0 };

  int32_T c12_b_i;
  int32_T c12_b_j;
  int32_T c12_i18;
  real_T c12_x;
  real_T c12_b_x;
  real_T c12_c_x;
  real_T c12_d_x;
  real_T c12_b_a;
  real_T c12_y;
  real_T c12_c_a;
  real_T c12_b_y;
  real_T c12_d_a;
  real_T c12_b_b;
  real_T c12_c_y;
  real_T c12_e_a;
  real_T c12_d_y;
  real_T c12_f_a;
  real_T c12_e_y;
  real_T c12_c_b;
  real_T c12_f_y;
  real_T c12_g_a;
  real_T c12_d_b;
  real_T c12_g_y;
  real_T c12_h_a;
  real_T c12_h_y;
  real_T c12_i_a;
  real_T c12_i_y;
  real_T c12_e_b;
  real_T c12_j_y;
  real_T c12_j_a;
  real_T c12_f_b;
  real_T c12_k_y;
  real_T c12_k_a;
  real_T c12_l_y;
  real_T c12_l_a;
  real_T c12_m_y;
  real_T c12_g_b;
  real_T c12_n_y;
  real_T c12_m_a;
  real_T c12_h_b;
  real_T c12_o_y;
  real_T c12_n_a;
  real_T c12_p_y;
  real_T c12_o_a;
  real_T c12_q_y;
  real_T c12_p_a;
  real_T c12_i_b;
  real_T c12_r_y;
  real_T c12_q_a;
  real_T c12_s_y;
  real_T c12_s_a;
  real_T c12_t_y;
  real_T c12_j_b;
  real_T c12_u_y;
  real_T c12_t_a;
  real_T c12_k_b;
  real_T c12_v_y;
  real_T c12_u_a;
  real_T c12_w_y;
  real_T c12_v_a;
  real_T c12_x_y;
  real_T c12_l_b;
  real_T c12_y_y;
  real_T c12_w_a;
  real_T c12_m_b;
  real_T c12_ab_y;
  real_T c12_x_a;
  real_T c12_bb_y;
  real_T c12_y_a;
  real_T c12_cb_y;
  real_T c12_n_b;
  real_T c12_db_y;
  real_T c12_ab_a;
  real_T c12_o_b;
  real_T c12_eb_y;
  real_T c12_bb_a;
  real_T c12_fb_y;
  real_T c12_cb_a;
  real_T c12_gb_y;
  real_T c12_db_a;
  real_T c12_p_b;
  real_T c12_hb_y;
  int32_T c12_c_j;
  int32_T c12_c_i;
  int32_T c12_i19;
  int32_T c12_d_i;
  int32_T c12_d_j;
  int32_T c12_i20;
  real_T c12_e_x;
  real_T c12_f_x;
  real_T c12_g_x;
  real_T c12_h_x;
  real_T c12_eb_a;
  real_T c12_ib_y;
  real_T c12_fb_a;
  real_T c12_jb_y;
  real_T c12_gb_a;
  real_T c12_q_b;
  real_T c12_kb_y;
  real_T c12_hb_a;
  real_T c12_lb_y;
  real_T c12_ib_a;
  real_T c12_mb_y;
  real_T c12_s_b;
  real_T c12_nb_y;
  real_T c12_jb_a;
  real_T c12_t_b;
  real_T c12_ob_y;
  real_T c12_kb_a;
  real_T c12_pb_y;
  real_T c12_lb_a;
  real_T c12_qb_y;
  real_T c12_u_b;
  real_T c12_rb_y;
  real_T c12_mb_a;
  real_T c12_v_b;
  real_T c12_sb_y;
  real_T c12_nb_a;
  real_T c12_tb_y;
  real_T c12_ob_a;
  real_T c12_ub_y;
  real_T c12_w_b;
  real_T c12_vb_y;
  real_T c12_pb_a;
  real_T c12_x_b;
  real_T c12_wb_y;
  real_T c12_qb_a;
  real_T c12_xb_y;
  real_T c12_rb_a;
  real_T c12_yb_y;
  real_T c12_sb_a;
  real_T c12_y_b;
  real_T c12_ac_y;
  real_T c12_tb_a;
  real_T c12_bc_y;
  real_T c12_ub_a;
  real_T c12_cc_y;
  real_T c12_ab_b;
  real_T c12_dc_y;
  real_T c12_vb_a;
  real_T c12_bb_b;
  real_T c12_ec_y;
  real_T c12_wb_a;
  real_T c12_fc_y;
  real_T c12_xb_a;
  real_T c12_gc_y;
  real_T c12_cb_b;
  real_T c12_hc_y;
  real_T c12_yb_a;
  real_T c12_db_b;
  real_T c12_ic_y;
  real_T c12_ac_a;
  real_T c12_jc_y;
  real_T c12_bc_a;
  real_T c12_kc_y;
  real_T c12_eb_b;
  real_T c12_lc_y;
  real_T c12_cc_a;
  real_T c12_fb_b;
  real_T c12_mc_y;
  real_T c12_dc_a;
  real_T c12_nc_y;
  real_T c12_ec_a;
  real_T c12_oc_y;
  real_T c12_fc_a;
  real_T c12_gb_b;
  real_T c12_pc_y;
  int32_T c12_e_j;
  int32_T c12_e_i;
  int32_T c12_i21;
  int32_T c12_i22;
  int32_T c12_i23;
  int32_T c12_i24;
  int32_T c12_f_i;
  real_T c12_A;
  real_T c12_i_x;
  real_T c12_j_x;
  real_T c12_b_A;
  real_T c12_k_x;
  real_T c12_l_x;
  real_T c12_c_A;
  real_T c12_m_x;
  real_T c12_n_x;
  int32_T c12_i25;
  int32_T c12_i26;
  int32_T c12_i27;
  real_T c12_b_AC[3];
  int32_T c12_i28;
  real_T c12_b_AB[3];
  real_T c12_dv6[3];
  int32_T c12_i29;
  int32_T c12_i30;
  real_T c12_hb_b[3];
  int32_T c12_i31;
  real_T c12_gc_a;
  int32_T c12_i32;
  int32_T c12_i33;
  int32_T c12_i34;
  int32_T c12_i35;
  real_T c12_b_r_m[3];
  int32_T c12_i36;
  real_T c12_b_PanelForce[3];
  real_T c12_dv7[3];
  int32_T c12_i37;
  int32_T c12_i38;
  int32_T c12_i39;
  int32_T c12_i40;
  int32_T c12_i41;
  int32_T c12_i42;
  int32_T c12_i43;
  real_T (*c12_b_BodyForce)[3];
  real_T (*c12_b_BodyMoment)[3];
  real_T (*c12_b_TotalArea)[3];
  real_T (*c12_c_PanelForce)[3];
  real_T (*c12_b_Disp2)[6];
  real_T (*c12_b_STL)[23742];
  c12_c_PanelForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
  c12_b_TotalArea = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 3);
  c12_b_BodyMoment = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c12_b_Disp2 = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 1);
  c12_b_BodyForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c12_b_STL = (real_T (*)[23742])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 8U, chartInstance->c12_sfEvent);
  for (c12_i14 = 0; c12_i14 < 23742; c12_i14++) {
    c12_STL[c12_i14] = (*c12_b_STL)[c12_i14];
  }

  for (c12_i15 = 0; c12_i15 < 6; c12_i15++) {
    c12_Disp2[c12_i15] = (*c12_b_Disp2)[c12_i15];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 35U, 35U, c12_debug_family_names,
    c12_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c12_a, 0U, c12_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_b, 1U, c12_d_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_c, 2U, c12_d_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c12_axisRotx, 3U, c12_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c12_axisRoty, 4U, c12_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_dZ, 5U, c12_d_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_angleRotx, 6U, c12_d_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_angleRoty, 7U, c12_d_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_i, 8U, c12_d_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_j, 9U, c12_d_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_q, 10U, c12_e_sf_marshallOut,
    c12_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_costhetay, 11U, c12_d_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_sinthetay, 12U, c12_d_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_costhetax, 13U, c12_d_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_sinthetax, 14U, c12_d_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_x_m, 15U, c12_d_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_y_m, 16U, c12_d_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_z_m, 17U, c12_d_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_r_m, 18U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_r_a, 19U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_r_b, 20U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_r_c, 21U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_AB, 22U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_AC, 23U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_CP, 24U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_area, 25U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_PanelMoment, 26U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_nargin, 27U, c12_d_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c12_nargout, 28U, c12_d_sf_marshallOut,
    c12_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c12_STL, 29U, c12_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c12_Disp2, 30U, c12_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_BodyForce, 31U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_BodyMoment, 32U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_TotalArea, 33U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c12_PanelForce, 34U, c12_sf_marshallOut,
    c12_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 15);
  c12_a = 2638.0;
  c12_b = 3.0;
  c12_c = 3.0;
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 20);
  for (c12_i16 = 0; c12_i16 < 3; c12_i16++) {
    c12_axisRotx[c12_i16] = c12_dv4[c12_i16];
  }

  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 21);
  for (c12_i17 = 0; c12_i17 < 3; c12_i17++) {
    c12_axisRoty[c12_i17] = c12_dv5[c12_i17];
  }

  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 22);
  c12_dZ = c12_Disp2[2];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 23);
  c12_angleRotx = c12_Disp2[3];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 24);
  c12_angleRoty = c12_Disp2[4];
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 27);
  c12_i = 1.0;
  c12_b_i = 0;
  while (c12_b_i < 2638) {
    c12_i = 1.0 + (real_T)c12_b_i;
    CV_EML_FOR(0, 1, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 28);
    c12_j = 1.0;
    c12_b_j = 0;
    while (c12_b_j < 3) {
      c12_j = 1.0 + (real_T)c12_b_j;
      CV_EML_FOR(0, 1, 1, 1);
      _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 29);
      for (c12_i18 = 0; c12_i18 < 3; c12_i18++) {
        c12_q[c12_i18] = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 32);
      if (CV_EML_IF(0, 1, 0, c12_angleRoty != 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 34);
        c12_x = c12_angleRoty;
        c12_costhetay = c12_x;
        c12_b_x = c12_costhetay;
        c12_costhetay = c12_b_x;
        c12_costhetay = muDoubleScalarCos(c12_costhetay);
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 35);
        c12_c_x = c12_angleRoty;
        c12_sinthetay = c12_c_x;
        c12_d_x = c12_sinthetay;
        c12_sinthetay = c12_d_x;
        c12_sinthetay = muDoubleScalarSin(c12_sinthetay);
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 37);
        c12_b_a = 1.0 - c12_costhetay;
        c12_y = c12_b_a * 0.0;
        c12_c_a = c12_y;
        c12_b_y = c12_c_a * 0.0;
        c12_d_a = c12_costhetay + c12_b_y;
        c12_b_b = c12_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 2638 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c12_j), 1, 3, 2, 0)
                            - 1)) - 1];
        c12_c_y = c12_d_a * c12_b_b;
        c12_q[0] += c12_c_y;
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 38);
        c12_e_a = 1.0 - c12_costhetay;
        c12_d_y = c12_e_a * 0.0;
        c12_f_a = c12_d_y;
        c12_e_y = c12_f_a;
        c12_c_b = c12_sinthetay;
        c12_f_y = 0.0 * c12_c_b;
        c12_g_a = c12_e_y - c12_f_y;
        c12_d_b = c12_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 2638 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c12_j), 1, 3, 2, 0)
                            - 1)) + 7913];
        c12_g_y = c12_g_a * c12_d_b;
        c12_q[0] += c12_g_y;
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 39);
        c12_h_a = 1.0 - c12_costhetay;
        c12_h_y = c12_h_a * 0.0;
        c12_i_a = c12_h_y;
        c12_i_y = c12_i_a * 0.0;
        c12_e_b = c12_sinthetay;
        c12_j_y = c12_e_b;
        c12_j_a = c12_i_y + c12_j_y;
        c12_f_b = c12_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 2638 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c12_j), 1, 3, 2, 0)
                            - 1)) + 15827];
        c12_k_y = c12_j_a * c12_f_b;
        c12_q[0] += c12_k_y;
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 41);
        c12_k_a = 1.0 - c12_costhetay;
        c12_l_y = c12_k_a * 0.0;
        c12_l_a = c12_l_y;
        c12_m_y = c12_l_a;
        c12_g_b = c12_sinthetay;
        c12_n_y = 0.0 * c12_g_b;
        c12_m_a = c12_m_y + c12_n_y;
        c12_h_b = c12_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 2638 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c12_j), 1, 3, 2, 0)
                            - 1)) - 1];
        c12_o_y = c12_m_a * c12_h_b;
        c12_q[1] += c12_o_y;
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 42);
        c12_n_a = 1.0 - c12_costhetay;
        c12_p_y = c12_n_a;
        c12_o_a = c12_p_y;
        c12_q_y = c12_o_a;
        c12_p_a = c12_costhetay + c12_q_y;
        c12_i_b = c12_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 2638 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c12_j), 1, 3, 2, 0)
                            - 1)) + 7913];
        c12_r_y = c12_p_a * c12_i_b;
        c12_q[1] += c12_r_y;
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 43);
        c12_q_a = 1.0 - c12_costhetay;
        c12_s_y = c12_q_a;
        c12_s_a = c12_s_y;
        c12_t_y = c12_s_a * 0.0;
        c12_j_b = c12_sinthetay;
        c12_u_y = 0.0 * c12_j_b;
        c12_t_a = c12_t_y - c12_u_y;
        c12_k_b = c12_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 2638 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c12_j), 1, 3, 2, 0)
                            - 1)) + 15827];
        c12_v_y = c12_t_a * c12_k_b;
        c12_q[1] += c12_v_y;
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 45);
        c12_u_a = 1.0 - c12_costhetay;
        c12_w_y = c12_u_a * 0.0;
        c12_v_a = c12_w_y;
        c12_x_y = c12_v_a * 0.0;
        c12_l_b = c12_sinthetay;
        c12_y_y = c12_l_b;
        c12_w_a = c12_x_y - c12_y_y;
        c12_m_b = c12_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 2638 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c12_j), 1, 3, 2, 0)
                            - 1)) - 1];
        c12_ab_y = c12_w_a * c12_m_b;
        c12_q[2] += c12_ab_y;
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 46);
        c12_x_a = 1.0 - c12_costhetay;
        c12_bb_y = c12_x_a;
        c12_y_a = c12_bb_y;
        c12_cb_y = c12_y_a * 0.0;
        c12_n_b = c12_sinthetay;
        c12_db_y = 0.0 * c12_n_b;
        c12_ab_a = c12_cb_y + c12_db_y;
        c12_o_b = c12_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 2638 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c12_j), 1, 3, 2, 0)
                            - 1)) + 7913];
        c12_eb_y = c12_ab_a * c12_o_b;
        c12_q[2] += c12_eb_y;
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 47);
        c12_bb_a = 1.0 - c12_costhetay;
        c12_fb_y = c12_bb_a * 0.0;
        c12_cb_a = c12_fb_y;
        c12_gb_y = c12_cb_a * 0.0;
        c12_db_a = c12_costhetay + c12_gb_y;
        c12_p_b = c12_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 2638 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c12_j), 1, 3, 2, 0)
                            - 1)) + 15827];
        c12_hb_y = c12_db_a * c12_p_b;
        c12_q[2] += c12_hb_y;
      }

      _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 51);
      if (CV_EML_IF(0, 1, 1, c12_angleRoty != 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 53);
        c12_c_j = (int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL", (int32_T)
          _SFD_INTEGER_CHECK("j", c12_j), 1, 3, 2, 0) - 1;
        c12_c_i = (int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL", (int32_T)
          _SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) - 1;
        for (c12_i19 = 0; c12_i19 < 3; c12_i19++) {
          c12_STL[(c12_c_i + 2638 * c12_c_j) + 7914 * c12_i19] = c12_q[c12_i19];
        }
      }

      c12_b_j++;
      _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 1, 0);
    c12_b_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 0, 0);
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 58);
  c12_i = 1.0;
  c12_d_i = 0;
  while (c12_d_i < 2638) {
    c12_i = 1.0 + (real_T)c12_d_i;
    CV_EML_FOR(0, 1, 2, 1);
    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 59);
    c12_j = 1.0;
    c12_d_j = 0;
    while (c12_d_j < 3) {
      c12_j = 1.0 + (real_T)c12_d_j;
      CV_EML_FOR(0, 1, 3, 1);
      _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 60);
      for (c12_i20 = 0; c12_i20 < 3; c12_i20++) {
        c12_q[c12_i20] = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 62);
      if (CV_EML_IF(0, 1, 2, c12_angleRotx != 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 64);
        c12_e_x = c12_angleRotx;
        c12_costhetax = c12_e_x;
        c12_f_x = c12_costhetax;
        c12_costhetax = c12_f_x;
        c12_costhetax = muDoubleScalarCos(c12_costhetax);
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 65);
        c12_g_x = c12_angleRotx;
        c12_sinthetax = c12_g_x;
        c12_h_x = c12_sinthetax;
        c12_sinthetax = c12_h_x;
        c12_sinthetax = muDoubleScalarSin(c12_sinthetax);
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 67);
        c12_eb_a = 1.0 - c12_costhetax;
        c12_ib_y = c12_eb_a;
        c12_fb_a = c12_ib_y;
        c12_jb_y = c12_fb_a;
        c12_gb_a = c12_costhetax + c12_jb_y;
        c12_q_b = c12_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 2638 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c12_j), 1, 3, 2, 0)
                            - 1)) - 1];
        c12_kb_y = c12_gb_a * c12_q_b;
        c12_q[0] += c12_kb_y;
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 68);
        c12_hb_a = 1.0 - c12_costhetax;
        c12_lb_y = c12_hb_a;
        c12_ib_a = c12_lb_y;
        c12_mb_y = c12_ib_a * 0.0;
        c12_s_b = c12_sinthetax;
        c12_nb_y = 0.0 * c12_s_b;
        c12_jb_a = c12_mb_y - c12_nb_y;
        c12_t_b = c12_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 2638 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c12_j), 1, 3, 2, 0)
                            - 1)) + 7913];
        c12_ob_y = c12_jb_a * c12_t_b;
        c12_q[0] += c12_ob_y;
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 69);
        c12_kb_a = 1.0 - c12_costhetax;
        c12_pb_y = c12_kb_a;
        c12_lb_a = c12_pb_y;
        c12_qb_y = c12_lb_a * 0.0;
        c12_u_b = c12_sinthetax;
        c12_rb_y = 0.0 * c12_u_b;
        c12_mb_a = c12_qb_y + c12_rb_y;
        c12_v_b = c12_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 2638 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c12_j), 1, 3, 2, 0)
                            - 1)) + 15827];
        c12_sb_y = c12_mb_a * c12_v_b;
        c12_q[0] += c12_sb_y;
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 71);
        c12_nb_a = 1.0 - c12_costhetax;
        c12_tb_y = c12_nb_a;
        c12_ob_a = c12_tb_y;
        c12_ub_y = c12_ob_a * 0.0;
        c12_w_b = c12_sinthetax;
        c12_vb_y = 0.0 * c12_w_b;
        c12_pb_a = c12_ub_y + c12_vb_y;
        c12_x_b = c12_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 2638 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c12_j), 1, 3, 2, 0)
                            - 1)) - 1];
        c12_wb_y = c12_pb_a * c12_x_b;
        c12_q[1] += c12_wb_y;
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 72);
        c12_qb_a = 1.0 - c12_costhetax;
        c12_xb_y = c12_qb_a * 0.0;
        c12_rb_a = c12_xb_y;
        c12_yb_y = c12_rb_a * 0.0;
        c12_sb_a = c12_costhetax + c12_yb_y;
        c12_y_b = c12_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 2638 *
                           ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("j", c12_j), 1, 3, 2, 0)
                            - 1)) + 7913];
        c12_ac_y = c12_sb_a * c12_y_b;
        c12_q[1] += c12_ac_y;
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 73);
        c12_tb_a = 1.0 - c12_costhetax;
        c12_bc_y = c12_tb_a * 0.0;
        c12_ub_a = c12_bc_y;
        c12_cc_y = c12_ub_a * 0.0;
        c12_ab_b = c12_sinthetax;
        c12_dc_y = c12_ab_b;
        c12_vb_a = c12_cc_y - c12_dc_y;
        c12_bb_b = c12_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1,
          0) + 2638 * ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("j", c12_j), 1, 3, 2, 0) - 1)) + 15827];
        c12_ec_y = c12_vb_a * c12_bb_b;
        c12_q[1] += c12_ec_y;
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 75);
        c12_wb_a = 1.0 - c12_costhetax;
        c12_fc_y = c12_wb_a;
        c12_xb_a = c12_fc_y;
        c12_gc_y = c12_xb_a * 0.0;
        c12_cb_b = c12_sinthetax;
        c12_hc_y = 0.0 * c12_cb_b;
        c12_yb_a = c12_gc_y - c12_hc_y;
        c12_db_b = c12_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1,
          0) + 2638 * ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("j", c12_j), 1, 3, 2, 0) - 1)) - 1];
        c12_ic_y = c12_yb_a * c12_db_b;
        c12_q[2] += c12_ic_y;
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 76);
        c12_ac_a = 1.0 - c12_costhetax;
        c12_jc_y = c12_ac_a * 0.0;
        c12_bc_a = c12_jc_y;
        c12_kc_y = c12_bc_a * 0.0;
        c12_eb_b = c12_sinthetax;
        c12_lc_y = c12_eb_b;
        c12_cc_a = c12_kc_y + c12_lc_y;
        c12_fb_b = c12_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1,
          0) + 2638 * ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("j", c12_j), 1, 3, 2, 0) - 1)) + 7913];
        c12_mc_y = c12_cc_a * c12_fb_b;
        c12_q[2] += c12_mc_y;
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 77);
        c12_dc_a = 1.0 - c12_costhetax;
        c12_nc_y = c12_dc_a * 0.0;
        c12_ec_a = c12_nc_y;
        c12_oc_y = c12_ec_a * 0.0;
        c12_fc_a = c12_costhetax + c12_oc_y;
        c12_gb_b = c12_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1,
          0) + 2638 * ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("j", c12_j), 1, 3, 2, 0) - 1)) + 15827];
        c12_pc_y = c12_fc_a * c12_gb_b;
        c12_q[2] += c12_pc_y;
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 79);
        c12_q[2] += c12_dZ;
      } else {
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 82);
        c12_q[0] = c12_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1,
          0) + 2638 * ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("j", c12_j), 1, 3, 2, 0) - 1)) - 1];
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 83);
        c12_q[1] = c12_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1,
          0) + 2638 * ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("j", c12_j), 1, 3, 2, 0) - 1)) + 7913];
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 84);
        c12_q[2] = c12_STL[((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                             (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1,
          0) + 2638 * ((int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
          (int32_T)_SFD_INTEGER_CHECK("j", c12_j), 1, 3, 2, 0) - 1)) + 15827] +
          c12_dZ;
      }

      _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 88);
      if (CV_EML_IF(0, 1, 3, c12_q[2] > 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 89);
        c12_q[2] = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 93);
      c12_e_j = (int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL", (int32_T)
        _SFD_INTEGER_CHECK("j", c12_j), 1, 3, 2, 0) - 1;
      c12_e_i = (int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL", (int32_T)
        _SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) - 1;
      for (c12_i21 = 0; c12_i21 < 3; c12_i21++) {
        c12_STL[(c12_e_i + 2638 * c12_e_j) + 7914 * c12_i21] = c12_q[c12_i21];
      }

      c12_d_j++;
      _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 3, 0);
    c12_d_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 2, 0);
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 98);
  for (c12_i22 = 0; c12_i22 < 3; c12_i22++) {
    c12_BodyForce[c12_i22] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 99);
  for (c12_i23 = 0; c12_i23 < 3; c12_i23++) {
    c12_BodyMoment[c12_i23] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 100);
  for (c12_i24 = 0; c12_i24 < 3; c12_i24++) {
    c12_TotalArea[c12_i24] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 101);
  c12_i = 1.0;
  c12_f_i = 0;
  while (c12_f_i < 2638) {
    c12_i = 1.0 + (real_T)c12_f_i;
    CV_EML_FOR(0, 1, 4, 1);
    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 102);
    c12_A = (c12_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
              (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) - 1] +
             c12_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
              (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 2637]) +
      c12_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL", (int32_T)
      _SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 5275];
    c12_i_x = c12_A;
    c12_j_x = c12_i_x;
    c12_x_m = c12_j_x / 3.0;
    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 103);
    c12_b_A = (c12_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 7913]
               + c12_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 10551])
      + c12_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL", (int32_T)
      _SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 13189];
    c12_k_x = c12_b_A;
    c12_l_x = c12_k_x;
    c12_y_m = c12_l_x / 3.0;
    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 104);
    c12_c_A = (c12_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 15827]
               + c12_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
                (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 18465])
      + c12_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL", (int32_T)
      _SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 21103];
    c12_m_x = c12_c_A;
    c12_n_x = c12_m_x;
    c12_z_m = c12_n_x / 3.0;
    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 105);
    c12_r_m[0] = c12_x_m;
    c12_r_m[1] = c12_y_m;
    c12_r_m[2] = c12_z_m;
    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 107);
    c12_r_a[0] = c12_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
      (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) - 1];
    c12_r_a[1] = c12_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
      (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 7913];
    c12_r_a[2] = c12_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
      (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 15827];
    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 108);
    c12_r_b[0] = c12_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
      (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 2637];
    c12_r_b[1] = c12_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
      (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 10551];
    c12_r_b[2] = c12_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
      (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 18465];
    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 109);
    c12_r_c[0] = c12_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
      (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 5275];
    c12_r_c[1] = c12_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
      (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 13189];
    c12_r_c[2] = c12_STL[(int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("STL",
      (int32_T)_SFD_INTEGER_CHECK("i", c12_i), 1, 2638, 1, 0) + 21103];
    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 111);
    for (c12_i25 = 0; c12_i25 < 3; c12_i25++) {
      c12_AB[c12_i25] = c12_r_b[c12_i25] - c12_r_a[c12_i25];
    }

    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 112);
    for (c12_i26 = 0; c12_i26 < 3; c12_i26++) {
      c12_AC[c12_i26] = c12_r_c[c12_i26] - c12_r_a[c12_i26];
    }

    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 113);
    for (c12_i27 = 0; c12_i27 < 3; c12_i27++) {
      c12_b_AC[c12_i27] = c12_AC[c12_i27];
    }

    for (c12_i28 = 0; c12_i28 < 3; c12_i28++) {
      c12_b_AB[c12_i28] = c12_AB[c12_i28];
    }

    c12_cross(chartInstance, c12_b_AC, c12_b_AB, c12_dv6);
    for (c12_i29 = 0; c12_i29 < 3; c12_i29++) {
      c12_CP[c12_i29] = c12_dv6[c12_i29];
    }

    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 114);
    for (c12_i30 = 0; c12_i30 < 3; c12_i30++) {
      c12_hb_b[c12_i30] = c12_CP[c12_i30];
    }

    for (c12_i31 = 0; c12_i31 < 3; c12_i31++) {
      c12_area[c12_i31] = 0.5 * c12_hb_b[c12_i31];
    }

    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 116);
    c12_gc_a = -c12_z_m;
    for (c12_i32 = 0; c12_i32 < 3; c12_i32++) {
      c12_hb_b[c12_i32] = c12_area[c12_i32];
    }

    for (c12_i33 = 0; c12_i33 < 3; c12_i33++) {
      c12_PanelForce[c12_i33] = c12_gc_a * c12_hb_b[c12_i33];
    }

    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 117);
    for (c12_i34 = 0; c12_i34 < 3; c12_i34++) {
      c12_BodyForce[c12_i34] += c12_PanelForce[c12_i34];
    }

    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 119);
    for (c12_i35 = 0; c12_i35 < 3; c12_i35++) {
      c12_b_r_m[c12_i35] = c12_r_m[c12_i35];
    }

    for (c12_i36 = 0; c12_i36 < 3; c12_i36++) {
      c12_b_PanelForce[c12_i36] = c12_PanelForce[c12_i36];
    }

    c12_cross(chartInstance, c12_b_r_m, c12_b_PanelForce, c12_dv7);
    for (c12_i37 = 0; c12_i37 < 3; c12_i37++) {
      c12_PanelMoment[c12_i37] = c12_dv7[c12_i37];
    }

    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 120);
    for (c12_i38 = 0; c12_i38 < 3; c12_i38++) {
      c12_BodyMoment[c12_i38] += c12_PanelMoment[c12_i38];
    }

    _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, 121);
    for (c12_i39 = 0; c12_i39 < 3; c12_i39++) {
      c12_TotalArea[c12_i39] += c12_area[c12_i39];
    }

    c12_f_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 4, 0);
  _SFD_EML_CALL(0U, chartInstance->c12_sfEvent, -121);
  _SFD_SYMBOL_SCOPE_POP();
  for (c12_i40 = 0; c12_i40 < 3; c12_i40++) {
    (*c12_b_BodyForce)[c12_i40] = c12_BodyForce[c12_i40];
  }

  for (c12_i41 = 0; c12_i41 < 3; c12_i41++) {
    (*c12_b_BodyMoment)[c12_i41] = c12_BodyMoment[c12_i41];
  }

  for (c12_i42 = 0; c12_i42 < 3; c12_i42++) {
    (*c12_b_TotalArea)[c12_i42] = c12_TotalArea[c12_i42];
  }

  for (c12_i43 = 0; c12_i43 < 3; c12_i43++) {
    (*c12_c_PanelForce)[c12_i43] = c12_PanelForce[c12_i43];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, chartInstance->c12_sfEvent);
}

static void initSimStructsc12_WEC_Sim_Driver(SFc12_WEC_Sim_DriverInstanceStruct *
  chartInstance)
{
}

static void registerMessagesc12_WEC_Sim_Driver
  (SFc12_WEC_Sim_DriverInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c12_machineNumber, uint32_T
  c12_chartNumber)
{
}

static const mxArray *c12_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  int32_T c12_i44;
  real_T c12_b_inData[3];
  int32_T c12_i45;
  real_T c12_u[3];
  const mxArray *c12_y = NULL;
  SFc12_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc12_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  for (c12_i44 = 0; c12_i44 < 3; c12_i44++) {
    c12_b_inData[c12_i44] = (*(real_T (*)[3])c12_inData)[c12_i44];
  }

  for (c12_i45 = 0; c12_i45 < 3; c12_i45++) {
    c12_u[c12_i45] = c12_b_inData[c12_i45];
  }

  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", c12_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, FALSE);
  return c12_mxArrayOutData;
}

static void c12_emlrt_marshallIn(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c12_PanelForce, const char_T *c12_identifier,
  real_T c12_y[3])
{
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_PanelForce), &c12_thisId,
    c12_y);
  sf_mex_destroy(&c12_PanelForce);
}

static void c12_b_emlrt_marshallIn(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId,
  real_T c12_y[3])
{
  real_T c12_dv8[3];
  int32_T c12_i46;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), c12_dv8, 1, 0, 0U, 1, 0U, 1, 3);
  for (c12_i46 = 0; c12_i46 < 3; c12_i46++) {
    c12_y[c12_i46] = c12_dv8[c12_i46];
  }

  sf_mex_destroy(&c12_u);
}

static void c12_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData)
{
  const mxArray *c12_PanelForce;
  const char_T *c12_identifier;
  emlrtMsgIdentifier c12_thisId;
  real_T c12_y[3];
  int32_T c12_i47;
  SFc12_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc12_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c12_PanelForce = sf_mex_dup(c12_mxArrayInData);
  c12_identifier = c12_varName;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_PanelForce), &c12_thisId,
    c12_y);
  sf_mex_destroy(&c12_PanelForce);
  for (c12_i47 = 0; c12_i47 < 3; c12_i47++) {
    (*(real_T (*)[3])c12_outData)[c12_i47] = c12_y[c12_i47];
  }

  sf_mex_destroy(&c12_mxArrayInData);
}

static const mxArray *c12_b_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  int32_T c12_i48;
  real_T c12_b_inData[6];
  int32_T c12_i49;
  real_T c12_u[6];
  const mxArray *c12_y = NULL;
  SFc12_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc12_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  for (c12_i48 = 0; c12_i48 < 6; c12_i48++) {
    c12_b_inData[c12_i48] = (*(real_T (*)[6])c12_inData)[c12_i48];
  }

  for (c12_i49 = 0; c12_i49 < 6; c12_i49++) {
    c12_u[c12_i49] = c12_b_inData[c12_i49];
  }

  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", c12_u, 0, 0U, 1U, 0U, 1, 6), FALSE);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, FALSE);
  return c12_mxArrayOutData;
}

static const mxArray *c12_c_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  int32_T c12_i50;
  int32_T c12_i51;
  int32_T c12_i52;
  int32_T c12_i53;
  int32_T c12_i54;
  static real_T c12_b_inData[23742];
  int32_T c12_i55;
  int32_T c12_i56;
  int32_T c12_i57;
  int32_T c12_i58;
  int32_T c12_i59;
  real_T c12_u[23742];
  const mxArray *c12_y = NULL;
  SFc12_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc12_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  c12_i50 = 0;
  for (c12_i51 = 0; c12_i51 < 3; c12_i51++) {
    c12_i52 = 0;
    for (c12_i53 = 0; c12_i53 < 3; c12_i53++) {
      for (c12_i54 = 0; c12_i54 < 2638; c12_i54++) {
        c12_b_inData[(c12_i54 + c12_i52) + c12_i50] = (*(real_T (*)[23742])
          c12_inData)[(c12_i54 + c12_i52) + c12_i50];
      }

      c12_i52 += 2638;
    }

    c12_i50 += 7914;
  }

  c12_i55 = 0;
  for (c12_i56 = 0; c12_i56 < 3; c12_i56++) {
    c12_i57 = 0;
    for (c12_i58 = 0; c12_i58 < 3; c12_i58++) {
      for (c12_i59 = 0; c12_i59 < 2638; c12_i59++) {
        c12_u[(c12_i59 + c12_i57) + c12_i55] = c12_b_inData[(c12_i59 + c12_i57)
          + c12_i55];
      }

      c12_i57 += 2638;
    }

    c12_i55 += 7914;
  }

  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", c12_u, 0, 0U, 1U, 0U, 3, 2638, 3, 3),
                FALSE);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, FALSE);
  return c12_mxArrayOutData;
}

static const mxArray *c12_d_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  real_T c12_u;
  const mxArray *c12_y = NULL;
  SFc12_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc12_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  c12_u = *(real_T *)c12_inData;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", &c12_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, FALSE);
  return c12_mxArrayOutData;
}

static real_T c12_c_emlrt_marshallIn(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  real_T c12_y;
  real_T c12_d0;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_d0, 1, 0, 0U, 0, 0U, 0);
  c12_y = c12_d0;
  sf_mex_destroy(&c12_u);
  return c12_y;
}

static void c12_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData)
{
  const mxArray *c12_nargout;
  const char_T *c12_identifier;
  emlrtMsgIdentifier c12_thisId;
  real_T c12_y;
  SFc12_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc12_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c12_nargout = sf_mex_dup(c12_mxArrayInData);
  c12_identifier = c12_varName;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_nargout),
    &c12_thisId);
  sf_mex_destroy(&c12_nargout);
  *(real_T *)c12_outData = c12_y;
  sf_mex_destroy(&c12_mxArrayInData);
}

static const mxArray *c12_e_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  int32_T c12_i60;
  real_T c12_b_inData[3];
  int32_T c12_i61;
  real_T c12_u[3];
  const mxArray *c12_y = NULL;
  SFc12_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc12_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  for (c12_i60 = 0; c12_i60 < 3; c12_i60++) {
    c12_b_inData[c12_i60] = (*(real_T (*)[3])c12_inData)[c12_i60];
  }

  for (c12_i61 = 0; c12_i61 < 3; c12_i61++) {
    c12_u[c12_i61] = c12_b_inData[c12_i61];
  }

  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", c12_u, 0, 0U, 1U, 0U, 2, 1, 3), FALSE);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, FALSE);
  return c12_mxArrayOutData;
}

static void c12_d_emlrt_marshallIn(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId,
  real_T c12_y[3])
{
  real_T c12_dv9[3];
  int32_T c12_i62;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), c12_dv9, 1, 0, 0U, 1, 0U, 2, 1,
                3);
  for (c12_i62 = 0; c12_i62 < 3; c12_i62++) {
    c12_y[c12_i62] = c12_dv9[c12_i62];
  }

  sf_mex_destroy(&c12_u);
}

static void c12_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData)
{
  const mxArray *c12_q;
  const char_T *c12_identifier;
  emlrtMsgIdentifier c12_thisId;
  real_T c12_y[3];
  int32_T c12_i63;
  SFc12_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc12_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c12_q = sf_mex_dup(c12_mxArrayInData);
  c12_identifier = c12_varName;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_q), &c12_thisId, c12_y);
  sf_mex_destroy(&c12_q);
  for (c12_i63 = 0; c12_i63 < 3; c12_i63++) {
    (*(real_T (*)[3])c12_outData)[c12_i63] = c12_y[c12_i63];
  }

  sf_mex_destroy(&c12_mxArrayInData);
}

const mxArray *sf_c12_WEC_Sim_Driver_get_eml_resolved_functions_info(void)
{
  const mxArray *c12_nameCaptureInfo;
  c12_ResolvedFunctionInfo c12_info[11];
  c12_ResolvedFunctionInfo (*c12_b_info)[11];
  const mxArray *c12_m0 = NULL;
  int32_T c12_i64;
  c12_ResolvedFunctionInfo *c12_r0;
  c12_nameCaptureInfo = NULL;
  c12_nameCaptureInfo = NULL;
  c12_b_info = (c12_ResolvedFunctionInfo (*)[11])c12_info;
  (*c12_b_info)[0].context = "";
  (*c12_b_info)[0].name = "cos";
  (*c12_b_info)[0].dominantType = "double";
  (*c12_b_info)[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  (*c12_b_info)[0].fileTimeLo = 1343859172U;
  (*c12_b_info)[0].fileTimeHi = 0U;
  (*c12_b_info)[0].mFileTimeLo = 0U;
  (*c12_b_info)[0].mFileTimeHi = 0U;
  (*c12_b_info)[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  (*c12_b_info)[1].name = "eml_scalar_cos";
  (*c12_b_info)[1].dominantType = "double";
  (*c12_b_info)[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  (*c12_b_info)[1].fileTimeLo = 1286847522U;
  (*c12_b_info)[1].fileTimeHi = 0U;
  (*c12_b_info)[1].mFileTimeLo = 0U;
  (*c12_b_info)[1].mFileTimeHi = 0U;
  (*c12_b_info)[2].context = "";
  (*c12_b_info)[2].name = "sin";
  (*c12_b_info)[2].dominantType = "double";
  (*c12_b_info)[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  (*c12_b_info)[2].fileTimeLo = 1343859186U;
  (*c12_b_info)[2].fileTimeHi = 0U;
  (*c12_b_info)[2].mFileTimeLo = 0U;
  (*c12_b_info)[2].mFileTimeHi = 0U;
  (*c12_b_info)[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  (*c12_b_info)[3].name = "eml_scalar_sin";
  (*c12_b_info)[3].dominantType = "double";
  (*c12_b_info)[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  (*c12_b_info)[3].fileTimeLo = 1286847536U;
  (*c12_b_info)[3].fileTimeHi = 0U;
  (*c12_b_info)[3].mFileTimeLo = 0U;
  (*c12_b_info)[3].mFileTimeHi = 0U;
  (*c12_b_info)[4].context = "";
  (*c12_b_info)[4].name = "mtimes";
  (*c12_b_info)[4].dominantType = "double";
  (*c12_b_info)[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c12_b_info)[4].fileTimeLo = 1289548492U;
  (*c12_b_info)[4].fileTimeHi = 0U;
  (*c12_b_info)[4].mFileTimeLo = 0U;
  (*c12_b_info)[4].mFileTimeHi = 0U;
  (*c12_b_info)[5].context = "";
  (*c12_b_info)[5].name = "mrdivide";
  (*c12_b_info)[5].dominantType = "double";
  (*c12_b_info)[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  (*c12_b_info)[5].fileTimeLo = 1357980348U;
  (*c12_b_info)[5].fileTimeHi = 0U;
  (*c12_b_info)[5].mFileTimeLo = 1319758766U;
  (*c12_b_info)[5].mFileTimeHi = 0U;
  (*c12_b_info)[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  (*c12_b_info)[6].name = "rdivide";
  (*c12_b_info)[6].dominantType = "double";
  (*c12_b_info)[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c12_b_info)[6].fileTimeLo = 1346539188U;
  (*c12_b_info)[6].fileTimeHi = 0U;
  (*c12_b_info)[6].mFileTimeLo = 0U;
  (*c12_b_info)[6].mFileTimeHi = 0U;
  (*c12_b_info)[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c12_b_info)[7].name = "eml_scalexp_compatible";
  (*c12_b_info)[7].dominantType = "double";
  (*c12_b_info)[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  (*c12_b_info)[7].fileTimeLo = 1286847596U;
  (*c12_b_info)[7].fileTimeHi = 0U;
  (*c12_b_info)[7].mFileTimeLo = 0U;
  (*c12_b_info)[7].mFileTimeHi = 0U;
  (*c12_b_info)[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c12_b_info)[8].name = "eml_div";
  (*c12_b_info)[8].dominantType = "double";
  (*c12_b_info)[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  (*c12_b_info)[8].fileTimeLo = 1313376610U;
  (*c12_b_info)[8].fileTimeHi = 0U;
  (*c12_b_info)[8].mFileTimeLo = 0U;
  (*c12_b_info)[8].mFileTimeHi = 0U;
  (*c12_b_info)[9].context = "";
  (*c12_b_info)[9].name = "cross";
  (*c12_b_info)[9].dominantType = "double";
  (*c12_b_info)[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  (*c12_b_info)[9].fileTimeLo = 1286847642U;
  (*c12_b_info)[9].fileTimeHi = 0U;
  (*c12_b_info)[9].mFileTimeLo = 0U;
  (*c12_b_info)[9].mFileTimeHi = 0U;
  (*c12_b_info)[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  (*c12_b_info)[10].name = "mtimes";
  (*c12_b_info)[10].dominantType = "double";
  (*c12_b_info)[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  (*c12_b_info)[10].fileTimeLo = 1289548492U;
  (*c12_b_info)[10].fileTimeHi = 0U;
  (*c12_b_info)[10].mFileTimeLo = 0U;
  (*c12_b_info)[10].mFileTimeHi = 0U;
  sf_mex_assign(&c12_m0, sf_mex_createstruct("nameCaptureInfo", 1, 11), FALSE);
  for (c12_i64 = 0; c12_i64 < 11; c12_i64++) {
    c12_r0 = &c12_info[c12_i64];
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", c12_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c12_r0->context)), "context", "nameCaptureInfo",
                    c12_i64);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", c12_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c12_r0->name)), "name", "nameCaptureInfo",
                    c12_i64);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo",
      c12_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c12_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c12_i64);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", c12_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c12_r0->resolved)), "resolved",
                    "nameCaptureInfo", c12_i64);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", &c12_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c12_i64);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo", &c12_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c12_i64);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo",
      &c12_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c12_i64);
    sf_mex_addfield(c12_m0, sf_mex_create("nameCaptureInfo",
      &c12_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c12_i64);
  }

  sf_mex_assign(&c12_nameCaptureInfo, c12_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c12_nameCaptureInfo);
  return c12_nameCaptureInfo;
}

static void c12_cross(SFc12_WEC_Sim_DriverInstanceStruct *chartInstance, real_T
                      c12_a[3], real_T c12_b[3], real_T c12_c[3])
{
  real_T c12_b_a;
  real_T c12_b_b;
  real_T c12_y;
  real_T c12_c_a;
  real_T c12_c_b;
  real_T c12_b_y;
  real_T c12_c1;
  real_T c12_d_a;
  real_T c12_d_b;
  real_T c12_c_y;
  real_T c12_e_a;
  real_T c12_e_b;
  real_T c12_d_y;
  real_T c12_c2;
  real_T c12_f_a;
  real_T c12_f_b;
  real_T c12_e_y;
  real_T c12_g_a;
  real_T c12_g_b;
  real_T c12_f_y;
  real_T c12_c3;
  c12_b_a = c12_a[1];
  c12_b_b = c12_b[2];
  c12_y = c12_b_a * c12_b_b;
  c12_c_a = c12_a[2];
  c12_c_b = c12_b[1];
  c12_b_y = c12_c_a * c12_c_b;
  c12_c1 = c12_y - c12_b_y;
  c12_d_a = c12_a[2];
  c12_d_b = c12_b[0];
  c12_c_y = c12_d_a * c12_d_b;
  c12_e_a = c12_a[0];
  c12_e_b = c12_b[2];
  c12_d_y = c12_e_a * c12_e_b;
  c12_c2 = c12_c_y - c12_d_y;
  c12_f_a = c12_a[0];
  c12_f_b = c12_b[1];
  c12_e_y = c12_f_a * c12_f_b;
  c12_g_a = c12_a[1];
  c12_g_b = c12_b[0];
  c12_f_y = c12_g_a * c12_g_b;
  c12_c3 = c12_e_y - c12_f_y;
  c12_c[0] = c12_c1;
  c12_c[1] = c12_c2;
  c12_c[2] = c12_c3;
}

static const mxArray *c12_f_sf_marshallOut(void *chartInstanceVoid, void
  *c12_inData)
{
  const mxArray *c12_mxArrayOutData = NULL;
  int32_T c12_u;
  const mxArray *c12_y = NULL;
  SFc12_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc12_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c12_mxArrayOutData = NULL;
  c12_u = *(int32_T *)c12_inData;
  c12_y = NULL;
  sf_mex_assign(&c12_y, sf_mex_create("y", &c12_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c12_mxArrayOutData, c12_y, FALSE);
  return c12_mxArrayOutData;
}

static int32_T c12_e_emlrt_marshallIn(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  int32_T c12_y;
  int32_T c12_i65;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_i65, 1, 6, 0U, 0, 0U, 0);
  c12_y = c12_i65;
  sf_mex_destroy(&c12_u);
  return c12_y;
}

static void c12_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c12_mxArrayInData, const char_T *c12_varName, void *c12_outData)
{
  const mxArray *c12_b_sfEvent;
  const char_T *c12_identifier;
  emlrtMsgIdentifier c12_thisId;
  int32_T c12_y;
  SFc12_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc12_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c12_b_sfEvent = sf_mex_dup(c12_mxArrayInData);
  c12_identifier = c12_varName;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c12_b_sfEvent),
    &c12_thisId);
  sf_mex_destroy(&c12_b_sfEvent);
  *(int32_T *)c12_outData = c12_y;
  sf_mex_destroy(&c12_mxArrayInData);
}

static uint8_T c12_f_emlrt_marshallIn(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c12_b_is_active_c12_WEC_Sim_Driver, const
  char_T *c12_identifier)
{
  uint8_T c12_y;
  emlrtMsgIdentifier c12_thisId;
  c12_thisId.fIdentifier = c12_identifier;
  c12_thisId.fParent = NULL;
  c12_y = c12_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c12_b_is_active_c12_WEC_Sim_Driver), &c12_thisId);
  sf_mex_destroy(&c12_b_is_active_c12_WEC_Sim_Driver);
  return c12_y;
}

static uint8_T c12_g_emlrt_marshallIn(SFc12_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c12_u, const emlrtMsgIdentifier *c12_parentId)
{
  uint8_T c12_y;
  uint8_T c12_u0;
  sf_mex_import(c12_parentId, sf_mex_dup(c12_u), &c12_u0, 1, 3, 0U, 0, 0U, 0);
  c12_y = c12_u0;
  sf_mex_destroy(&c12_u);
  return c12_y;
}

static void init_dsm_address_info(SFc12_WEC_Sim_DriverInstanceStruct
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

void sf_c12_WEC_Sim_Driver_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4229768429U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3570865086U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2265978713U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2684208662U);
}

mxArray *sf_c12_WEC_Sim_Driver_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("AETn7A5Y8ilI7BSvNvFlPC");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,3,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2638);
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

mxArray *sf_c12_WEC_Sim_Driver_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c12_WEC_Sim_Driver(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[5],T\"BodyForce\",},{M[1],M[10],T\"BodyMoment\",},{M[1],M[14],T\"PanelForce\",},{M[1],M[13],T\"TotalArea\",},{M[8],M[0],T\"is_active_c12_WEC_Sim_Driver\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c12_WEC_Sim_Driver_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc12_WEC_Sim_DriverInstanceStruct *chartInstance;
    chartInstance = (SFc12_WEC_Sim_DriverInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _WEC_Sim_DriverMachineNumber_,
           12,
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
          _SFD_SET_DATA_PROPS(2,1,1,0,"Disp2");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,5038);
        _SFD_CV_INIT_EML_IF(0,1,0,1114,1131,-1,2289);
        _SFD_CV_INIT_EML_IF(0,1,1,2298,2315,-1,2379);
        _SFD_CV_INIT_EML_IF(0,1,2,2493,2510,3663,3807);
        _SFD_CV_INIT_EML_IF(0,1,3,3860,3871,-1,3905);
        _SFD_CV_INIT_EML_FOR(0,1,0,1006,1018,2391);
        _SFD_CV_INIT_EML_FOR(0,1,1,1022,1034,2387);
        _SFD_CV_INIT_EML_FOR(0,1,2,2393,2405,3978);
        _SFD_CV_INIT_EML_FOR(0,1,3,2409,2421,3974);
        _SFD_CV_INIT_EML_FOR(0,1,4,4095,4107,4965);
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
          dimVector[0]= 2638;
          dimVector[1]= 3;
          dimVector[2]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,3,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_sf_marshallOut,(MexInFcnForType)
            c12_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_sf_marshallOut,(MexInFcnForType)
            c12_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_sf_marshallOut,(MexInFcnForType)
            c12_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c12_sf_marshallOut,(MexInFcnForType)
            c12_sf_marshallIn);
        }

        {
          real_T (*c12_STL)[23742];
          real_T (*c12_BodyForce)[3];
          real_T (*c12_Disp2)[6];
          real_T (*c12_BodyMoment)[3];
          real_T (*c12_TotalArea)[3];
          real_T (*c12_PanelForce)[3];
          c12_PanelForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
            4);
          c12_TotalArea = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
            3);
          c12_BodyMoment = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
            2);
          c12_Disp2 = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 1);
          c12_BodyForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
            1);
          c12_STL = (real_T (*)[23742])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c12_STL);
          _SFD_SET_DATA_VALUE_PTR(1U, *c12_BodyForce);
          _SFD_SET_DATA_VALUE_PTR(2U, *c12_Disp2);
          _SFD_SET_DATA_VALUE_PTR(3U, *c12_BodyMoment);
          _SFD_SET_DATA_VALUE_PTR(4U, *c12_TotalArea);
          _SFD_SET_DATA_VALUE_PTR(5U, *c12_PanelForce);
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
  return "6TfD7PikORBiWvkfCgnAqC";
}

static void sf_opaque_initialize_c12_WEC_Sim_Driver(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc12_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c12_WEC_Sim_Driver((SFc12_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar);
  initialize_c12_WEC_Sim_Driver((SFc12_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c12_WEC_Sim_Driver(void *chartInstanceVar)
{
  enable_c12_WEC_Sim_Driver((SFc12_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c12_WEC_Sim_Driver(void *chartInstanceVar)
{
  disable_c12_WEC_Sim_Driver((SFc12_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c12_WEC_Sim_Driver(void *chartInstanceVar)
{
  sf_c12_WEC_Sim_Driver((SFc12_WEC_Sim_DriverInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c12_WEC_Sim_Driver(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c12_WEC_Sim_Driver
    ((SFc12_WEC_Sim_DriverInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c12_WEC_Sim_Driver();/* state var info */
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

extern void sf_internal_set_sim_state_c12_WEC_Sim_Driver(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c12_WEC_Sim_Driver();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c12_WEC_Sim_Driver((SFc12_WEC_Sim_DriverInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c12_WEC_Sim_Driver(SimStruct* S)
{
  return sf_internal_get_sim_state_c12_WEC_Sim_Driver(S);
}

static void sf_opaque_set_sim_state_c12_WEC_Sim_Driver(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c12_WEC_Sim_Driver(S, st);
}

static void sf_opaque_terminate_c12_WEC_Sim_Driver(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc12_WEC_Sim_DriverInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_WEC_Sim_Driver_optimization_info();
    }

    finalize_c12_WEC_Sim_Driver((SFc12_WEC_Sim_DriverInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc12_WEC_Sim_Driver((SFc12_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c12_WEC_Sim_Driver(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c12_WEC_Sim_Driver((SFc12_WEC_Sim_DriverInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c12_WEC_Sim_Driver(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_WEC_Sim_Driver_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      12);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,12,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,12,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,12);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,12,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,12,4);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,12);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3883933890U));
  ssSetChecksum1(S,(3281902665U));
  ssSetChecksum2(S,(4141323080U));
  ssSetChecksum3(S,(3076412047U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c12_WEC_Sim_Driver(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c12_WEC_Sim_Driver(SimStruct *S)
{
  SFc12_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc12_WEC_Sim_DriverInstanceStruct *)utMalloc(sizeof
    (SFc12_WEC_Sim_DriverInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc12_WEC_Sim_DriverInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c12_WEC_Sim_Driver;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c12_WEC_Sim_Driver;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c12_WEC_Sim_Driver;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c12_WEC_Sim_Driver;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c12_WEC_Sim_Driver;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c12_WEC_Sim_Driver;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c12_WEC_Sim_Driver;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c12_WEC_Sim_Driver;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c12_WEC_Sim_Driver;
  chartInstance->chartInfo.mdlStart = mdlStart_c12_WEC_Sim_Driver;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c12_WEC_Sim_Driver;
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

void c12_WEC_Sim_Driver_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c12_WEC_Sim_Driver(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c12_WEC_Sim_Driver(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c12_WEC_Sim_Driver(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c12_WEC_Sim_Driver_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
