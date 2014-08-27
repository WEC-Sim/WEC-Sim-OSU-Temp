/* Include files */

#include <stddef.h>
#include "blas.h"
#include "WEC_Sim_Driver_sfun.h"
#include "c9_WEC_Sim_Driver.h"
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
static const char * c9_debug_family_names[64] = { "a", "b", "c", "axisRotx",
  "axisRoty", "dX", "dZ", "angleRotx", "angleRoty", "Amp", "k", "w", "d", "psi",
  "psi_l", "psi_avg", "psi_l_avg", "STL_l", "i", "j", "q_l", "q", "costhetay",
  "sinthetay", "costhetax", "sinthetax", "x_m", "y_m", "z_m", "r_m", "r_a",
  "r_b", "r_c", "AB", "AC", "CP", "area", "x_m_l", "y_m_l", "z_m_l", "r_m_l",
  "r_a_l", "r_b_l", "r_c_l", "AB_l", "AC_l", "CP_l", "area_l", "p_HS", "p_FK",
  "p_FK_l", "p_total", "PanelMoment", "nargin", "nargout", "STL", "t", "Disp",
  "nonlinear_params", "BodyForce", "BodyMoment", "psi_m", "p_FK_total",
  "p_FK_l_total" };

/* Function Declarations */
static void initialize_c9_WEC_Sim_Driver(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void initialize_params_c9_WEC_Sim_Driver
  (SFc9_WEC_Sim_DriverInstanceStruct *chartInstance);
static void enable_c9_WEC_Sim_Driver(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void disable_c9_WEC_Sim_Driver(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void c9_update_debugger_state_c9_WEC_Sim_Driver
  (SFc9_WEC_Sim_DriverInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c9_WEC_Sim_Driver
  (SFc9_WEC_Sim_DriverInstanceStruct *chartInstance);
static void set_sim_state_c9_WEC_Sim_Driver(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_st);
static void finalize_c9_WEC_Sim_Driver(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void sf_c9_WEC_Sim_Driver(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void c9_chartstep_c9_WEC_Sim_Driver(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void initSimStructsc9_WEC_Sim_Driver(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void registerMessagesc9_WEC_Sim_Driver(SFc9_WEC_Sim_DriverInstanceStruct *
  chartInstance);
static void init_script_number_translation(uint32_T c9_machineNumber, uint32_T
  c9_chartNumber);
static const mxArray *c9_sf_marshallOut(void *chartInstanceVoid, void *c9_inData);
static void c9_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct *chartInstance,
  const mxArray *c9_p_FK_l_total, const char_T *c9_identifier, real_T c9_y[3]);
static void c9_b_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId,
  real_T c9_y[3]);
static void c9_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static const mxArray *c9_b_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static real_T c9_c_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_psi_m, const char_T *c9_identifier);
static real_T c9_d_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void c9_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static const mxArray *c9_c_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static const mxArray *c9_d_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static const mxArray *c9_e_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static const mxArray *c9_f_sf_marshallOut(void *chartInstanceVoid, real_T
  c9_inData_data[1], int32_T c9_inData_sizes[2]);
static void c9_e_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId,
  real_T c9_y_data[1], int32_T c9_y_sizes[2]);
static void c9_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, real_T c9_outData_data[1],
  int32_T c9_outData_sizes[2]);
static const mxArray *c9_g_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static void c9_f_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId,
  real_T c9_y[3]);
static void c9_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static const mxArray *c9_h_sf_marshallOut(void *chartInstanceVoid, real_T
  c9_inData_data[3], int32_T c9_inData_sizes[2]);
static void c9_g_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId,
  real_T c9_y_data[3], int32_T c9_y_sizes[2]);
static void c9_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, real_T c9_outData_data[3],
  int32_T c9_outData_sizes[2]);
static const mxArray *c9_i_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static void c9_h_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId,
  real_T c9_y[3]);
static void c9_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static void c9_i_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId,
  real_T c9_y[9846]);
static void c9_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static const mxArray *c9_j_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static void c9_j_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId,
  real_T c9_y[3282]);
static void c9_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static void c9_info_helper(c9_ResolvedFunctionInfo c9_info[31]);
static void c9_cross(SFc9_WEC_Sim_DriverInstanceStruct *chartInstance, real_T
                     c9_a[3], real_T c9_b[3], real_T c9_c[3]);
static void c9_cosh(SFc9_WEC_Sim_DriverInstanceStruct *chartInstance, real_T
                    c9_x_data[1], int32_T c9_x_sizes[2], real_T c9_b_x_data[1],
                    int32_T c9_b_x_sizes[2]);
static const mxArray *c9_k_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData);
static int32_T c9_k_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void c9_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData);
static uint8_T c9_l_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_b_is_active_c9_WEC_Sim_Driver, const char_T *
  c9_identifier);
static uint8_T c9_m_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId);
static void c9_b_cosh(SFc9_WEC_Sim_DriverInstanceStruct *chartInstance, real_T
                      c9_x_data[1], int32_T c9_x_sizes[2]);
static void init_dsm_address_info(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c9_WEC_Sim_Driver(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
  chartInstance->c9_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c9_is_active_c9_WEC_Sim_Driver = 0U;
}

static void initialize_params_c9_WEC_Sim_Driver
  (SFc9_WEC_Sim_DriverInstanceStruct *chartInstance)
{
}

static void enable_c9_WEC_Sim_Driver(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c9_WEC_Sim_Driver(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c9_update_debugger_state_c9_WEC_Sim_Driver
  (SFc9_WEC_Sim_DriverInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c9_WEC_Sim_Driver
  (SFc9_WEC_Sim_DriverInstanceStruct *chartInstance)
{
  const mxArray *c9_st;
  const mxArray *c9_y = NULL;
  int32_T c9_i0;
  real_T c9_u[3];
  const mxArray *c9_b_y = NULL;
  int32_T c9_i1;
  real_T c9_b_u[3];
  const mxArray *c9_c_y = NULL;
  int32_T c9_i2;
  real_T c9_c_u[3];
  const mxArray *c9_d_y = NULL;
  int32_T c9_i3;
  real_T c9_d_u[3];
  const mxArray *c9_e_y = NULL;
  real_T c9_hoistedGlobal;
  real_T c9_e_u;
  const mxArray *c9_f_y = NULL;
  uint8_T c9_b_hoistedGlobal;
  uint8_T c9_f_u;
  const mxArray *c9_g_y = NULL;
  real_T *c9_psi_m;
  real_T (*c9_p_FK_total)[3];
  real_T (*c9_p_FK_l_total)[3];
  real_T (*c9_BodyMoment)[3];
  real_T (*c9_BodyForce)[3];
  c9_p_FK_l_total = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 5);
  c9_p_FK_total = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
  c9_psi_m = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c9_BodyMoment = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c9_BodyForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c9_st = NULL;
  c9_st = NULL;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_createcellarray(6), FALSE);
  for (c9_i0 = 0; c9_i0 < 3; c9_i0++) {
    c9_u[c9_i0] = (*c9_BodyForce)[c9_i0];
  }

  c9_b_y = NULL;
  sf_mex_assign(&c9_b_y, sf_mex_create("y", c9_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c9_y, 0, c9_b_y);
  for (c9_i1 = 0; c9_i1 < 3; c9_i1++) {
    c9_b_u[c9_i1] = (*c9_BodyMoment)[c9_i1];
  }

  c9_c_y = NULL;
  sf_mex_assign(&c9_c_y, sf_mex_create("y", c9_b_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c9_y, 1, c9_c_y);
  for (c9_i2 = 0; c9_i2 < 3; c9_i2++) {
    c9_c_u[c9_i2] = (*c9_p_FK_l_total)[c9_i2];
  }

  c9_d_y = NULL;
  sf_mex_assign(&c9_d_y, sf_mex_create("y", c9_c_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c9_y, 2, c9_d_y);
  for (c9_i3 = 0; c9_i3 < 3; c9_i3++) {
    c9_d_u[c9_i3] = (*c9_p_FK_total)[c9_i3];
  }

  c9_e_y = NULL;
  sf_mex_assign(&c9_e_y, sf_mex_create("y", c9_d_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c9_y, 3, c9_e_y);
  c9_hoistedGlobal = *c9_psi_m;
  c9_e_u = c9_hoistedGlobal;
  c9_f_y = NULL;
  sf_mex_assign(&c9_f_y, sf_mex_create("y", &c9_e_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c9_y, 4, c9_f_y);
  c9_b_hoistedGlobal = chartInstance->c9_is_active_c9_WEC_Sim_Driver;
  c9_f_u = c9_b_hoistedGlobal;
  c9_g_y = NULL;
  sf_mex_assign(&c9_g_y, sf_mex_create("y", &c9_f_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c9_y, 5, c9_g_y);
  sf_mex_assign(&c9_st, c9_y, FALSE);
  return c9_st;
}

static void set_sim_state_c9_WEC_Sim_Driver(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_st)
{
  const mxArray *c9_u;
  real_T c9_dv0[3];
  int32_T c9_i4;
  real_T c9_dv1[3];
  int32_T c9_i5;
  real_T c9_dv2[3];
  int32_T c9_i6;
  real_T c9_dv3[3];
  int32_T c9_i7;
  real_T *c9_psi_m;
  real_T (*c9_BodyForce)[3];
  real_T (*c9_BodyMoment)[3];
  real_T (*c9_p_FK_l_total)[3];
  real_T (*c9_p_FK_total)[3];
  c9_p_FK_l_total = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 5);
  c9_p_FK_total = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
  c9_psi_m = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c9_BodyMoment = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c9_BodyForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c9_doneDoubleBufferReInit = TRUE;
  c9_u = sf_mex_dup(c9_st);
  c9_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c9_u, 0)),
                      "BodyForce", c9_dv0);
  for (c9_i4 = 0; c9_i4 < 3; c9_i4++) {
    (*c9_BodyForce)[c9_i4] = c9_dv0[c9_i4];
  }

  c9_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c9_u, 1)),
                      "BodyMoment", c9_dv1);
  for (c9_i5 = 0; c9_i5 < 3; c9_i5++) {
    (*c9_BodyMoment)[c9_i5] = c9_dv1[c9_i5];
  }

  c9_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c9_u, 2)),
                      "p_FK_l_total", c9_dv2);
  for (c9_i6 = 0; c9_i6 < 3; c9_i6++) {
    (*c9_p_FK_l_total)[c9_i6] = c9_dv2[c9_i6];
  }

  c9_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c9_u, 3)),
                      "p_FK_total", c9_dv3);
  for (c9_i7 = 0; c9_i7 < 3; c9_i7++) {
    (*c9_p_FK_total)[c9_i7] = c9_dv3[c9_i7];
  }

  *c9_psi_m = c9_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c9_u, 4)), "psi_m");
  chartInstance->c9_is_active_c9_WEC_Sim_Driver = c9_l_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c9_u, 5)),
     "is_active_c9_WEC_Sim_Driver");
  sf_mex_destroy(&c9_u);
  c9_update_debugger_state_c9_WEC_Sim_Driver(chartInstance);
  sf_mex_destroy(&c9_st);
}

static void finalize_c9_WEC_Sim_Driver(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
}

static void sf_c9_WEC_Sim_Driver(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
  int32_T c9_i8;
  int32_T c9_i9;
  int32_T c9_i10;
  int32_T c9_i11;
  int32_T c9_i12;
  int32_T c9_i13;
  int32_T c9_i14;
  real_T *c9_t;
  real_T *c9_psi_m;
  real_T (*c9_p_FK_l_total)[3];
  real_T (*c9_p_FK_total)[3];
  real_T (*c9_nonlinear_params)[4];
  real_T (*c9_BodyMoment)[3];
  real_T (*c9_Disp)[6];
  real_T (*c9_BodyForce)[3];
  real_T (*c9_STL)[9846];
  c9_p_FK_l_total = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 5);
  c9_p_FK_total = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
  c9_psi_m = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c9_nonlinear_params = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 3);
  c9_BodyMoment = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c9_Disp = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 2);
  c9_BodyForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c9_t = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c9_STL = (real_T (*)[9846])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 7U, chartInstance->c9_sfEvent);
  for (c9_i8 = 0; c9_i8 < 9846; c9_i8++) {
    _SFD_DATA_RANGE_CHECK((*c9_STL)[c9_i8], 0U);
  }

  _SFD_DATA_RANGE_CHECK(*c9_t, 1U);
  for (c9_i9 = 0; c9_i9 < 3; c9_i9++) {
    _SFD_DATA_RANGE_CHECK((*c9_BodyForce)[c9_i9], 2U);
  }

  for (c9_i10 = 0; c9_i10 < 6; c9_i10++) {
    _SFD_DATA_RANGE_CHECK((*c9_Disp)[c9_i10], 3U);
  }

  for (c9_i11 = 0; c9_i11 < 3; c9_i11++) {
    _SFD_DATA_RANGE_CHECK((*c9_BodyMoment)[c9_i11], 4U);
  }

  for (c9_i12 = 0; c9_i12 < 4; c9_i12++) {
    _SFD_DATA_RANGE_CHECK((*c9_nonlinear_params)[c9_i12], 5U);
  }

  _SFD_DATA_RANGE_CHECK(*c9_psi_m, 6U);
  for (c9_i13 = 0; c9_i13 < 3; c9_i13++) {
    _SFD_DATA_RANGE_CHECK((*c9_p_FK_total)[c9_i13], 7U);
  }

  for (c9_i14 = 0; c9_i14 < 3; c9_i14++) {
    _SFD_DATA_RANGE_CHECK((*c9_p_FK_l_total)[c9_i14], 8U);
  }

  chartInstance->c9_sfEvent = CALL_EVENT;
  c9_chartstep_c9_WEC_Sim_Driver(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_WEC_Sim_DriverMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c9_chartstep_c9_WEC_Sim_Driver(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
  real_T c9_hoistedGlobal;
  int32_T c9_i15;
  static real_T c9_STL[9846];
  real_T c9_t;
  int32_T c9_i16;
  real_T c9_Disp[6];
  int32_T c9_i17;
  real_T c9_nonlinear_params[4];
  uint32_T c9_debug_family_var_map[64];
  real_T c9_a;
  real_T c9_b;
  real_T c9_c;
  real_T c9_axisRotx[3];
  real_T c9_axisRoty[3];
  real_T c9_dX;
  real_T c9_dZ;
  real_T c9_angleRotx;
  real_T c9_angleRoty;
  real_T c9_Amp;
  real_T c9_k;
  real_T c9_w;
  real_T c9_d;
  real_T c9_psi[3282];
  real_T c9_psi_l[3282];
  real_T c9_psi_avg[3282];
  real_T c9_psi_l_avg[3282];
  real_T c9_STL_l[9846];
  real_T c9_i;
  real_T c9_j;
  real_T c9_q_l[3];
  real_T c9_q[3];
  real_T c9_costhetay;
  real_T c9_sinthetay;
  real_T c9_costhetax;
  real_T c9_sinthetax;
  real_T c9_x_m;
  real_T c9_y_m;
  real_T c9_z_m;
  real_T c9_r_m[3];
  real_T c9_r_a[3];
  real_T c9_r_b[3];
  real_T c9_r_c[3];
  real_T c9_AB[3];
  real_T c9_AC[3];
  real_T c9_CP[3];
  real_T c9_area[3];
  real_T c9_x_m_l;
  real_T c9_y_m_l;
  real_T c9_z_m_l;
  real_T c9_r_m_l[3];
  real_T c9_r_a_l[3];
  real_T c9_r_b_l[3];
  real_T c9_r_c_l[3];
  real_T c9_AB_l[3];
  real_T c9_AC_l[3];
  real_T c9_CP_l[3];
  real_T c9_area_l[3];
  real_T c9_p_HS[3];
  int32_T c9_p_FK_sizes[2];
  real_T c9_p_FK_data[3];
  int32_T c9_p_FK_l_sizes[2];
  real_T c9_p_FK_l_data[3];
  real_T c9_p_total[3];
  real_T c9_PanelMoment[3];
  int32_T c9_psi_avg_sizes[2];
  real_T c9_psi_avg_data[1];
  int32_T c9_psi_l_avg_sizes[2];
  real_T c9_psi_l_avg_data[1];
  real_T c9_nargin = 4.0;
  real_T c9_nargout = 5.0;
  real_T c9_BodyForce[3];
  real_T c9_BodyMoment[3];
  real_T c9_psi_m;
  real_T c9_p_FK_total[3];
  real_T c9_p_FK_l_total[3];
  int32_T c9_i18;
  static real_T c9_dv4[3] = { 1.0, 0.0, 0.0 };

  int32_T c9_i19;
  static real_T c9_dv5[3] = { 0.0, 1.0, 0.0 };

  int32_T c9_i20;
  int32_T c9_i21;
  int32_T c9_i22;
  int32_T c9_i23;
  int32_T c9_i24;
  int32_T c9_b_i;
  int32_T c9_b_j;
  int32_T c9_i25;
  real_T c9_b_a;
  real_T c9_b_b;
  real_T c9_y;
  real_T c9_c_a;
  real_T c9_c_b;
  real_T c9_b_y;
  real_T c9_x;
  real_T c9_b_x;
  real_T c9_d_a;
  real_T c9_d_b;
  real_T c9_c_y;
  int32_T c9_c_j;
  int32_T c9_c_i;
  int32_T c9_i26;
  int32_T c9_d_i;
  int32_T c9_d_j;
  int32_T c9_i27;
  real_T c9_e_a;
  real_T c9_e_b;
  real_T c9_d_y;
  real_T c9_f_a;
  real_T c9_f_b;
  real_T c9_e_y;
  real_T c9_c_x;
  real_T c9_d_x;
  real_T c9_g_a;
  real_T c9_g_b;
  real_T c9_e_x;
  real_T c9_f_x;
  real_T c9_g_x;
  real_T c9_h_x;
  real_T c9_h_a;
  real_T c9_f_y;
  real_T c9_i_a;
  real_T c9_g_y;
  real_T c9_j_a;
  real_T c9_h_b;
  real_T c9_h_y;
  real_T c9_k_a;
  real_T c9_i_y;
  real_T c9_l_a;
  real_T c9_j_y;
  real_T c9_i_b;
  real_T c9_k_y;
  real_T c9_m_a;
  real_T c9_j_b;
  real_T c9_l_y;
  real_T c9_n_a;
  real_T c9_m_y;
  real_T c9_o_a;
  real_T c9_n_y;
  real_T c9_k_b;
  real_T c9_o_y;
  real_T c9_p_a;
  real_T c9_l_b;
  real_T c9_p_y;
  real_T c9_q_a;
  real_T c9_q_y;
  real_T c9_s_a;
  real_T c9_r_y;
  real_T c9_m_b;
  real_T c9_s_y;
  real_T c9_t_a;
  real_T c9_n_b;
  real_T c9_t_y;
  real_T c9_u_a;
  real_T c9_u_y;
  real_T c9_v_a;
  real_T c9_v_y;
  real_T c9_w_a;
  real_T c9_o_b;
  real_T c9_w_y;
  real_T c9_x_a;
  real_T c9_x_y;
  real_T c9_y_a;
  real_T c9_y_y;
  real_T c9_p_b;
  real_T c9_ab_y;
  real_T c9_ab_a;
  real_T c9_q_b;
  real_T c9_bb_y;
  real_T c9_bb_a;
  real_T c9_cb_y;
  real_T c9_cb_a;
  real_T c9_db_y;
  real_T c9_s_b;
  real_T c9_eb_y;
  real_T c9_db_a;
  real_T c9_t_b;
  real_T c9_fb_y;
  real_T c9_eb_a;
  real_T c9_gb_y;
  real_T c9_fb_a;
  real_T c9_hb_y;
  real_T c9_u_b;
  real_T c9_ib_y;
  real_T c9_gb_a;
  real_T c9_v_b;
  real_T c9_jb_y;
  real_T c9_hb_a;
  real_T c9_kb_y;
  real_T c9_ib_a;
  real_T c9_lb_y;
  real_T c9_jb_a;
  real_T c9_w_b;
  real_T c9_mb_y;
  int32_T c9_e_j;
  int32_T c9_e_i;
  int32_T c9_i28;
  int32_T c9_f_i;
  int32_T c9_f_j;
  int32_T c9_i29;
  real_T c9_i_x;
  real_T c9_j_x;
  real_T c9_k_x;
  real_T c9_l_x;
  real_T c9_kb_a;
  real_T c9_nb_y;
  real_T c9_lb_a;
  real_T c9_ob_y;
  real_T c9_mb_a;
  real_T c9_x_b;
  real_T c9_pb_y;
  real_T c9_nb_a;
  real_T c9_qb_y;
  real_T c9_ob_a;
  real_T c9_rb_y;
  real_T c9_y_b;
  real_T c9_sb_y;
  real_T c9_pb_a;
  real_T c9_ab_b;
  real_T c9_tb_y;
  real_T c9_qb_a;
  real_T c9_ub_y;
  real_T c9_rb_a;
  real_T c9_vb_y;
  real_T c9_bb_b;
  real_T c9_wb_y;
  real_T c9_sb_a;
  real_T c9_cb_b;
  real_T c9_xb_y;
  real_T c9_tb_a;
  real_T c9_yb_y;
  real_T c9_ub_a;
  real_T c9_ac_y;
  real_T c9_db_b;
  real_T c9_bc_y;
  real_T c9_vb_a;
  real_T c9_eb_b;
  real_T c9_cc_y;
  real_T c9_wb_a;
  real_T c9_dc_y;
  real_T c9_xb_a;
  real_T c9_ec_y;
  real_T c9_yb_a;
  real_T c9_fb_b;
  real_T c9_fc_y;
  real_T c9_ac_a;
  real_T c9_gc_y;
  real_T c9_bc_a;
  real_T c9_hc_y;
  real_T c9_gb_b;
  real_T c9_ic_y;
  real_T c9_cc_a;
  real_T c9_hb_b;
  real_T c9_jc_y;
  real_T c9_dc_a;
  real_T c9_kc_y;
  real_T c9_ec_a;
  real_T c9_lc_y;
  real_T c9_ib_b;
  real_T c9_mc_y;
  real_T c9_fc_a;
  real_T c9_jb_b;
  real_T c9_nc_y;
  real_T c9_gc_a;
  real_T c9_oc_y;
  real_T c9_hc_a;
  real_T c9_pc_y;
  real_T c9_kb_b;
  real_T c9_qc_y;
  real_T c9_ic_a;
  real_T c9_lb_b;
  real_T c9_rc_y;
  real_T c9_jc_a;
  real_T c9_sc_y;
  real_T c9_kc_a;
  real_T c9_tc_y;
  real_T c9_lc_a;
  real_T c9_mb_b;
  real_T c9_uc_y;
  real_T c9_mc_a;
  real_T c9_nb_b;
  real_T c9_vc_y;
  real_T c9_nc_a;
  real_T c9_ob_b;
  real_T c9_wc_y;
  real_T c9_m_x;
  real_T c9_n_x;
  real_T c9_oc_a;
  real_T c9_pb_b;
  real_T c9_xc_y;
  int32_T c9_g_j;
  int32_T c9_g_i;
  int32_T c9_i30;
  int32_T c9_i31;
  int32_T c9_i32;
  int32_T c9_i33;
  int32_T c9_i34;
  int32_T c9_h_i;
  real_T c9_A;
  real_T c9_o_x;
  real_T c9_p_x;
  real_T c9_b_A;
  real_T c9_q_x;
  real_T c9_r_x;
  real_T c9_c_A;
  real_T c9_s_x;
  real_T c9_t_x;
  int32_T c9_i35;
  int32_T c9_i36;
  int32_T c9_i37;
  real_T c9_b_AC[3];
  int32_T c9_i38;
  real_T c9_b_AB[3];
  real_T c9_dv6[3];
  int32_T c9_i39;
  int32_T c9_i40;
  real_T c9_qb_b[3];
  int32_T c9_i41;
  real_T c9_d_A;
  real_T c9_u_x;
  real_T c9_v_x;
  real_T c9_e_A;
  real_T c9_w_x;
  real_T c9_x_x;
  real_T c9_f_A;
  real_T c9_y_x;
  real_T c9_ab_x;
  int32_T c9_i42;
  int32_T c9_i43;
  int32_T c9_i44;
  real_T c9_b_AC_l[3];
  int32_T c9_i45;
  real_T c9_b_AB_l[3];
  real_T c9_dv7[3];
  int32_T c9_i46;
  int32_T c9_i47;
  int32_T c9_i48;
  real_T c9_g_A;
  real_T c9_bb_x;
  real_T c9_cb_x;
  real_T c9_yc_y;
  int32_T c9_b_psi_avg;
  int32_T c9_c_psi_avg;
  real_T c9_h_A;
  real_T c9_db_x;
  real_T c9_eb_x;
  real_T c9_ad_y;
  int32_T c9_b_psi_l_avg;
  int32_T c9_c_psi_l_avg;
  real_T c9_pc_a;
  int32_T c9_i49;
  int32_T c9_i50;
  int32_T c9_i51;
  int32_T c9_b_sizes[2];
  int32_T c9_rb_b;
  int32_T c9_sb_b;
  int32_T c9_loop_ub;
  int32_T c9_i52;
  real_T c9_b_data[1];
  int32_T c9_y_sizes[2];
  int32_T c9_i53;
  real_T c9_y_data[3];
  real_T c9_qc_a;
  int32_T c9_tb_b;
  int32_T c9_ub_b;
  int32_T c9_b_loop_ub;
  int32_T c9_i54;
  int32_T c9_vb_b;
  int32_T c9_wb_b;
  int32_T c9_xb_b;
  int32_T c9_yb_b;
  int32_T c9_c_loop_ub;
  int32_T c9_i55;
  int32_T c9_b_y_sizes[2];
  int32_T c9_i56;
  real_T c9_b_y_data[3];
  real_T c9_rc_a;
  real_T c9_ac_b;
  real_T c9_bd_y;
  real_T c9_fb_x;
  real_T c9_gb_x;
  real_T c9_B;
  real_T c9_cd_y;
  real_T c9_dd_y;
  int32_T c9_p_FK;
  int32_T c9_b_p_FK;
  int32_T c9_d_loop_ub;
  int32_T c9_i57;
  int32_T c9_i58;
  int32_T c9_bc_b;
  int32_T c9_cc_b;
  int32_T c9_e_loop_ub;
  int32_T c9_i59;
  int32_T c9_i60;
  real_T c9_sc_a;
  int32_T c9_dc_b;
  int32_T c9_ec_b;
  int32_T c9_f_loop_ub;
  int32_T c9_i61;
  int32_T c9_fc_b;
  int32_T c9_gc_b;
  int32_T c9_hc_b;
  int32_T c9_ic_b;
  int32_T c9_g_loop_ub;
  int32_T c9_i62;
  int32_T c9_i63;
  real_T c9_tc_a;
  real_T c9_jc_b;
  real_T c9_ed_y;
  real_T c9_hb_x;
  real_T c9_ib_x;
  real_T c9_b_B;
  real_T c9_fd_y;
  real_T c9_gd_y;
  int32_T c9_p_FK_l;
  int32_T c9_b_p_FK_l;
  int32_T c9_h_loop_ub;
  int32_T c9_i64;
  int32_T c9_i65;
  int32_T c9_i66;
  int32_T c9_i67;
  real_T c9_b_r_m[3];
  int32_T c9_i68;
  real_T c9_b_p_total[3];
  real_T c9_dv8[3];
  int32_T c9_i69;
  int32_T c9_i70;
  int32_T c9_i71;
  int32_T c9_i72;
  int32_T c9_i73;
  int32_T c9_i74;
  int32_T c9_i75;
  int32_T c9_i76;
  real_T *c9_b_psi_m;
  real_T *c9_b_t;
  real_T (*c9_b_BodyForce)[3];
  real_T (*c9_b_BodyMoment)[3];
  real_T (*c9_b_p_FK_total)[3];
  real_T (*c9_b_p_FK_l_total)[3];
  real_T (*c9_b_nonlinear_params)[4];
  real_T (*c9_b_Disp)[6];
  real_T (*c9_b_STL)[9846];
  c9_b_p_FK_l_total = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 5);
  c9_b_p_FK_total = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
  c9_b_psi_m = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c9_b_nonlinear_params = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S,
    3);
  c9_b_BodyMoment = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c9_b_Disp = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 2);
  c9_b_BodyForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c9_b_t = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c9_b_STL = (real_T (*)[9846])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 7U, chartInstance->c9_sfEvent);
  c9_hoistedGlobal = *c9_b_t;
  for (c9_i15 = 0; c9_i15 < 9846; c9_i15++) {
    c9_STL[c9_i15] = (*c9_b_STL)[c9_i15];
  }

  c9_t = c9_hoistedGlobal;
  for (c9_i16 = 0; c9_i16 < 6; c9_i16++) {
    c9_Disp[c9_i16] = (*c9_b_Disp)[c9_i16];
  }

  for (c9_i17 = 0; c9_i17 < 4; c9_i17++) {
    c9_nonlinear_params[c9_i17] = (*c9_b_nonlinear_params)[c9_i17];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 64U, 66U, c9_debug_family_names,
    c9_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c9_a, 0U, c9_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c9_b, 1U, c9_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_c, 2U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c9_axisRotx, 3U, c9_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c9_axisRoty, 4U, c9_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_dX, 5U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_dZ, 6U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_angleRotx, 7U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_angleRoty, 8U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_Amp, 9U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_k, 10U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_w, 11U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_d, 12U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_psi, 13U, c9_j_sf_marshallOut,
    c9_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_psi_l, 14U, c9_j_sf_marshallOut,
    c9_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_psi_avg, MAX_uint32_T,
    c9_j_sf_marshallOut, c9_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_psi_l_avg, MAX_uint32_T,
    c9_j_sf_marshallOut, c9_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_STL_l, 17U, c9_e_sf_marshallOut,
    c9_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_i, 18U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_j, 19U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_q_l, 20U, c9_i_sf_marshallOut,
    c9_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_q, 21U, c9_i_sf_marshallOut,
    c9_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_costhetay, 22U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_sinthetay, 23U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_costhetax, 24U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_sinthetax, 25U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_x_m, 26U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_y_m, 27U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_z_m, 28U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_r_m, 29U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_r_a, 30U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_r_b, 31U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_r_c, 32U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_AB, 33U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_AC, 34U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_CP, 35U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_area, 36U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_x_m_l, 37U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_y_m_l, 38U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_z_m_l, 39U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_r_m_l, 40U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_r_a_l, 41U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_r_b_l, 42U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_r_c_l, 43U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_AB_l, 44U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_AC_l, 45U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_CP_l, 46U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_area_l, 47U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_p_HS, 48U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c9_p_FK_data, (const int32_T *)
    &c9_p_FK_sizes, NULL, 0, 49, (void *)c9_h_sf_marshallOut, (void *)
    c9_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c9_p_FK_l_data, (const int32_T *)
    &c9_p_FK_l_sizes, NULL, 0, 50, (void *)c9_h_sf_marshallOut, (void *)
    c9_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_p_total, 51U, c9_g_sf_marshallOut,
    c9_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_PanelMoment, 52U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c9_psi_avg_data, (const int32_T *)
    &c9_psi_avg_sizes, NULL, 0, -1, (void *)c9_f_sf_marshallOut, (void *)
    c9_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c9_psi_l_avg_data, (const int32_T *)
    &c9_psi_l_avg_sizes, NULL, 0, -1, (void *)c9_f_sf_marshallOut, (void *)
    c9_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_nargin, 53U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_nargout, 54U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c9_STL, 55U, c9_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c9_t, 56U, c9_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c9_Disp, 57U, c9_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c9_nonlinear_params, 58U, c9_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_BodyForce, 59U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_BodyMoment, 60U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c9_psi_m, 61U, c9_b_sf_marshallOut,
    c9_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_p_FK_total, 62U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c9_p_FK_l_total, 63U, c9_sf_marshallOut,
    c9_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 15);
  c9_a = 1094.0;
  c9_b = 3.0;
  c9_c = 3.0;
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 20);
  for (c9_i18 = 0; c9_i18 < 3; c9_i18++) {
    c9_axisRotx[c9_i18] = c9_dv4[c9_i18];
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 21);
  for (c9_i19 = 0; c9_i19 < 3; c9_i19++) {
    c9_axisRoty[c9_i19] = c9_dv5[c9_i19];
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 22);
  c9_dX = c9_Disp[0];
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 23);
  c9_dZ = c9_Disp[2];
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 24);
  c9_angleRotx = c9_Disp[3];
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 25);
  c9_angleRoty = c9_Disp[4];
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 26);
  c9_Amp = c9_nonlinear_params[0];
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 27);
  c9_k = c9_nonlinear_params[1];
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 28);
  c9_w = c9_nonlinear_params[2];
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 29);
  c9_d = c9_nonlinear_params[3];
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 30);
  for (c9_i20 = 0; c9_i20 < 3282; c9_i20++) {
    c9_psi[c9_i20] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 31);
  for (c9_i21 = 0; c9_i21 < 3282; c9_i21++) {
    c9_psi_l[c9_i21] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 32);
  c9_psi_m = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 33);
  for (c9_i22 = 0; c9_i22 < 3282; c9_i22++) {
    c9_psi_avg[c9_i22] = 0.0;
  }

  _SFD_SYMBOL_SWITCH(15U, 15U);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 34);
  for (c9_i23 = 0; c9_i23 < 3282; c9_i23++) {
    c9_psi_l_avg[c9_i23] = 0.0;
  }

  _SFD_SYMBOL_SWITCH(16U, 16U);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 35);
  for (c9_i24 = 0; c9_i24 < 9846; c9_i24++) {
    c9_STL_l[c9_i24] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 38);
  c9_i = 1.0;
  c9_b_i = 0;
  while (c9_b_i < 1094) {
    c9_i = 1.0 + (real_T)c9_b_i;
    CV_EML_FOR(0, 1, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 39);
    c9_j = 1.0;
    c9_b_j = 0;
    while (c9_b_j < 3) {
      c9_j = 1.0 + (real_T)c9_b_j;
      CV_EML_FOR(0, 1, 1, 1);
      _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 40);
      for (c9_i25 = 0; c9_i25 < 3; c9_i25++) {
        c9_q_l[c9_i25] = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 42);
      c9_q_l[0] = c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) - 1];
      _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 43);
      c9_q_l[1] = c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) + 3281];
      _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 44);
      c9_q_l[2] = c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) + 6563] -
        17.606;
      _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 45);
      if (CV_EML_IF(0, 1, 0, c9_q_l[2] > 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 46);
        c9_q_l[2] = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 48);
      c9_b_a = c9_k;
      c9_b_b = c9_q_l[0] + c9_dX;
      c9_y = c9_b_a * c9_b_b;
      c9_c_a = c9_w;
      c9_c_b = c9_t;
      c9_b_y = c9_c_a * c9_c_b;
      c9_x = c9_y - c9_b_y;
      c9_b_x = c9_x;
      c9_b_x = muDoubleScalarCos(c9_b_x);
      c9_d_a = c9_Amp;
      c9_d_b = c9_b_x;
      c9_c_y = c9_d_a * c9_d_b;
      c9_psi_l[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) - 1] = c9_c_y;
      _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 50);
      c9_c_j = (int32_T)c9_j - 1;
      c9_c_i = (int32_T)c9_i - 1;
      for (c9_i26 = 0; c9_i26 < 3; c9_i26++) {
        c9_STL_l[(c9_c_i + 1094 * c9_c_j) + 3282 * c9_i26] = c9_q_l[c9_i26];
      }

      c9_b_j++;
      _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 1, 0);
    c9_b_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 0, 0);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 55);
  c9_i = 1.0;
  c9_d_i = 0;
  while (c9_d_i < 1094) {
    c9_i = 1.0 + (real_T)c9_d_i;
    CV_EML_FOR(0, 1, 2, 1);
    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 56);
    c9_j = 1.0;
    c9_d_j = 0;
    while (c9_d_j < 3) {
      c9_j = 1.0 + (real_T)c9_d_j;
      CV_EML_FOR(0, 1, 3, 1);
      _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 57);
      for (c9_i27 = 0; c9_i27 < 3; c9_i27++) {
        c9_q[c9_i27] = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 60);
      if (CV_EML_IF(0, 1, 1, c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1))
                    - 1] < 0.001)) {
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 61);
        c9_e_a = c9_k;
        c9_e_b = c9_dX;
        c9_d_y = c9_e_a * c9_e_b;
        c9_f_a = c9_w;
        c9_f_b = c9_t;
        c9_e_y = c9_f_a * c9_f_b;
        c9_c_x = c9_d_y - c9_e_y;
        c9_d_x = c9_c_x;
        c9_d_x = muDoubleScalarCos(c9_d_x);
        c9_g_a = c9_Amp;
        c9_g_b = c9_d_x;
        c9_psi_m = c9_g_a * c9_g_b;
      }

      _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 65);
      if (CV_EML_IF(0, 1, 2, c9_angleRoty != 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 67);
        c9_e_x = c9_angleRoty;
        c9_costhetay = c9_e_x;
        c9_f_x = c9_costhetay;
        c9_costhetay = c9_f_x;
        c9_costhetay = muDoubleScalarCos(c9_costhetay);
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 68);
        c9_g_x = c9_angleRoty;
        c9_sinthetay = c9_g_x;
        c9_h_x = c9_sinthetay;
        c9_sinthetay = c9_h_x;
        c9_sinthetay = muDoubleScalarSin(c9_sinthetay);
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 70);
        c9_h_a = 1.0 - c9_costhetay;
        c9_f_y = c9_h_a * 0.0;
        c9_i_a = c9_f_y;
        c9_g_y = c9_i_a * 0.0;
        c9_j_a = c9_costhetay + c9_g_y;
        c9_h_b = c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) - 1];
        c9_h_y = c9_j_a * c9_h_b;
        c9_q[0] = c9_h_y;
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 71);
        c9_k_a = 1.0 - c9_costhetay;
        c9_i_y = c9_k_a * 0.0;
        c9_l_a = c9_i_y;
        c9_j_y = c9_l_a;
        c9_i_b = c9_sinthetay;
        c9_k_y = 0.0 * c9_i_b;
        c9_m_a = c9_j_y - c9_k_y;
        c9_j_b = c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) + 3281];
        c9_l_y = c9_m_a * c9_j_b;
        c9_q[0] += c9_l_y;
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 72);
        c9_n_a = 1.0 - c9_costhetay;
        c9_m_y = c9_n_a * 0.0;
        c9_o_a = c9_m_y;
        c9_n_y = c9_o_a * 0.0;
        c9_k_b = c9_sinthetay;
        c9_o_y = c9_k_b;
        c9_p_a = c9_n_y + c9_o_y;
        c9_l_b = c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) + 6563];
        c9_p_y = c9_p_a * c9_l_b;
        c9_q[0] += c9_p_y;
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 74);
        c9_q_a = 1.0 - c9_costhetay;
        c9_q_y = c9_q_a * 0.0;
        c9_s_a = c9_q_y;
        c9_r_y = c9_s_a;
        c9_m_b = c9_sinthetay;
        c9_s_y = 0.0 * c9_m_b;
        c9_t_a = c9_r_y + c9_s_y;
        c9_n_b = c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) - 1];
        c9_t_y = c9_t_a * c9_n_b;
        c9_q[1] = c9_t_y;
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 75);
        c9_u_a = 1.0 - c9_costhetay;
        c9_u_y = c9_u_a;
        c9_v_a = c9_u_y;
        c9_v_y = c9_v_a;
        c9_w_a = c9_costhetay + c9_v_y;
        c9_o_b = c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) + 3281];
        c9_w_y = c9_w_a * c9_o_b;
        c9_q[1] += c9_w_y;
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 76);
        c9_x_a = 1.0 - c9_costhetay;
        c9_x_y = c9_x_a;
        c9_y_a = c9_x_y;
        c9_y_y = c9_y_a * 0.0;
        c9_p_b = c9_sinthetay;
        c9_ab_y = 0.0 * c9_p_b;
        c9_ab_a = c9_y_y - c9_ab_y;
        c9_q_b = c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) + 6563];
        c9_bb_y = c9_ab_a * c9_q_b;
        c9_q[1] += c9_bb_y;
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 78);
        c9_bb_a = 1.0 - c9_costhetay;
        c9_cb_y = c9_bb_a * 0.0;
        c9_cb_a = c9_cb_y;
        c9_db_y = c9_cb_a * 0.0;
        c9_s_b = c9_sinthetay;
        c9_eb_y = c9_s_b;
        c9_db_a = c9_db_y - c9_eb_y;
        c9_t_b = c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) - 1];
        c9_fb_y = c9_db_a * c9_t_b;
        c9_q[2] = c9_fb_y;
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 79);
        c9_eb_a = 1.0 - c9_costhetay;
        c9_gb_y = c9_eb_a;
        c9_fb_a = c9_gb_y;
        c9_hb_y = c9_fb_a * 0.0;
        c9_u_b = c9_sinthetay;
        c9_ib_y = 0.0 * c9_u_b;
        c9_gb_a = c9_hb_y + c9_ib_y;
        c9_v_b = c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) + 3281];
        c9_jb_y = c9_gb_a * c9_v_b;
        c9_q[2] += c9_jb_y;
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 80);
        c9_hb_a = 1.0 - c9_costhetay;
        c9_kb_y = c9_hb_a * 0.0;
        c9_ib_a = c9_kb_y;
        c9_lb_y = c9_ib_a * 0.0;
        c9_jb_a = c9_costhetay + c9_lb_y;
        c9_w_b = c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) + 6563];
        c9_mb_y = c9_jb_a * c9_w_b;
        c9_q[2] += c9_mb_y;
      }

      _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 84);
      if (CV_EML_IF(0, 1, 3, c9_angleRoty != 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 86);
        c9_e_j = (int32_T)c9_j - 1;
        c9_e_i = (int32_T)c9_i - 1;
        for (c9_i28 = 0; c9_i28 < 3; c9_i28++) {
          c9_STL[(c9_e_i + 1094 * c9_e_j) + 3282 * c9_i28] = c9_q[c9_i28];
        }
      }

      c9_d_j++;
      _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 3, 0);
    c9_d_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 2, 0);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 91);
  c9_i = 1.0;
  c9_f_i = 0;
  while (c9_f_i < 1094) {
    c9_i = 1.0 + (real_T)c9_f_i;
    CV_EML_FOR(0, 1, 4, 1);
    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 92);
    c9_j = 1.0;
    c9_f_j = 0;
    while (c9_f_j < 3) {
      c9_j = 1.0 + (real_T)c9_f_j;
      CV_EML_FOR(0, 1, 5, 1);
      _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 93);
      for (c9_i29 = 0; c9_i29 < 3; c9_i29++) {
        c9_q[c9_i29] = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 95);
      if (CV_EML_IF(0, 1, 4, c9_angleRotx != 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 97);
        c9_i_x = c9_angleRotx;
        c9_costhetax = c9_i_x;
        c9_j_x = c9_costhetax;
        c9_costhetax = c9_j_x;
        c9_costhetax = muDoubleScalarCos(c9_costhetax);
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 98);
        c9_k_x = c9_angleRotx;
        c9_sinthetax = c9_k_x;
        c9_l_x = c9_sinthetax;
        c9_sinthetax = c9_l_x;
        c9_sinthetax = muDoubleScalarSin(c9_sinthetax);
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 100);
        c9_kb_a = 1.0 - c9_costhetax;
        c9_nb_y = c9_kb_a;
        c9_lb_a = c9_nb_y;
        c9_ob_y = c9_lb_a;
        c9_mb_a = c9_costhetax + c9_ob_y;
        c9_x_b = c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) - 1];
        c9_pb_y = c9_mb_a * c9_x_b;
        c9_q[0] = c9_pb_y;
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 101);
        c9_nb_a = 1.0 - c9_costhetax;
        c9_qb_y = c9_nb_a;
        c9_ob_a = c9_qb_y;
        c9_rb_y = c9_ob_a * 0.0;
        c9_y_b = c9_sinthetax;
        c9_sb_y = 0.0 * c9_y_b;
        c9_pb_a = c9_rb_y - c9_sb_y;
        c9_ab_b = c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) + 3281];
        c9_tb_y = c9_pb_a * c9_ab_b;
        c9_q[0] += c9_tb_y;
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 102);
        c9_qb_a = 1.0 - c9_costhetax;
        c9_ub_y = c9_qb_a;
        c9_rb_a = c9_ub_y;
        c9_vb_y = c9_rb_a * 0.0;
        c9_bb_b = c9_sinthetax;
        c9_wb_y = 0.0 * c9_bb_b;
        c9_sb_a = c9_vb_y + c9_wb_y;
        c9_cb_b = c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) + 6563];
        c9_xb_y = c9_sb_a * c9_cb_b;
        c9_q[0] += c9_xb_y;
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 104);
        c9_tb_a = 1.0 - c9_costhetax;
        c9_yb_y = c9_tb_a;
        c9_ub_a = c9_yb_y;
        c9_ac_y = c9_ub_a * 0.0;
        c9_db_b = c9_sinthetax;
        c9_bc_y = 0.0 * c9_db_b;
        c9_vb_a = c9_ac_y + c9_bc_y;
        c9_eb_b = c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) - 1];
        c9_cc_y = c9_vb_a * c9_eb_b;
        c9_q[1] = c9_cc_y;
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 105);
        c9_wb_a = 1.0 - c9_costhetax;
        c9_dc_y = c9_wb_a * 0.0;
        c9_xb_a = c9_dc_y;
        c9_ec_y = c9_xb_a * 0.0;
        c9_yb_a = c9_costhetax + c9_ec_y;
        c9_fb_b = c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) + 3281];
        c9_fc_y = c9_yb_a * c9_fb_b;
        c9_q[1] += c9_fc_y;
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 106);
        c9_ac_a = 1.0 - c9_costhetax;
        c9_gc_y = c9_ac_a * 0.0;
        c9_bc_a = c9_gc_y;
        c9_hc_y = c9_bc_a * 0.0;
        c9_gb_b = c9_sinthetax;
        c9_ic_y = c9_gb_b;
        c9_cc_a = c9_hc_y - c9_ic_y;
        c9_hb_b = c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) + 6563];
        c9_jc_y = c9_cc_a * c9_hb_b;
        c9_q[1] += c9_jc_y;
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 108);
        c9_dc_a = 1.0 - c9_costhetax;
        c9_kc_y = c9_dc_a;
        c9_ec_a = c9_kc_y;
        c9_lc_y = c9_ec_a * 0.0;
        c9_ib_b = c9_sinthetax;
        c9_mc_y = 0.0 * c9_ib_b;
        c9_fc_a = c9_lc_y - c9_mc_y;
        c9_jb_b = c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) - 1];
        c9_nc_y = c9_fc_a * c9_jb_b;
        c9_q[2] = c9_nc_y;
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 109);
        c9_gc_a = 1.0 - c9_costhetax;
        c9_oc_y = c9_gc_a * 0.0;
        c9_hc_a = c9_oc_y;
        c9_pc_y = c9_hc_a * 0.0;
        c9_kb_b = c9_sinthetax;
        c9_qc_y = c9_kb_b;
        c9_ic_a = c9_pc_y + c9_qc_y;
        c9_lb_b = c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) + 3281];
        c9_rc_y = c9_ic_a * c9_lb_b;
        c9_q[2] += c9_rc_y;
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 110);
        c9_jc_a = 1.0 - c9_costhetax;
        c9_sc_y = c9_jc_a * 0.0;
        c9_kc_a = c9_sc_y;
        c9_tc_y = c9_kc_a * 0.0;
        c9_lc_a = c9_costhetax + c9_tc_y;
        c9_mb_b = c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) + 6563];
        c9_uc_y = c9_lc_a * c9_mb_b;
        c9_q[2] += c9_uc_y;
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 112);
        c9_q[2] += c9_dZ;
      } else {
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 115);
        c9_q[0] = c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) - 1];
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 116);
        c9_q[1] = c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) + 3281];
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 117);
        c9_q[2] = c9_STL[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) + 6563] +
          c9_dZ;
      }

      _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 121);
      c9_mc_a = c9_k;
      c9_nb_b = c9_q[0] + c9_dX;
      c9_vc_y = c9_mc_a * c9_nb_b;
      c9_nc_a = c9_w;
      c9_ob_b = c9_t;
      c9_wc_y = c9_nc_a * c9_ob_b;
      c9_m_x = c9_vc_y - c9_wc_y;
      c9_n_x = c9_m_x;
      c9_n_x = muDoubleScalarCos(c9_n_x);
      c9_oc_a = c9_Amp;
      c9_pb_b = c9_n_x;
      c9_xc_y = c9_oc_a * c9_pb_b;
      c9_psi[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) - 1] = c9_xc_y;
      _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 122);
      if (CV_EML_IF(0, 1, 5, c9_q[2] > c9_psi[((int32_T)c9_i + 1094 * ((int32_T)
             c9_j - 1)) - 1])) {
        _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 123);
        c9_q[2] = c9_psi[((int32_T)c9_i + 1094 * ((int32_T)c9_j - 1)) - 1];
      }

      _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 132U);
      c9_g_j = (int32_T)c9_j - 1;
      c9_g_i = (int32_T)c9_i - 1;
      for (c9_i30 = 0; c9_i30 < 3; c9_i30++) {
        c9_STL[(c9_g_i + 1094 * c9_g_j) + 3282 * c9_i30] = c9_q[c9_i30];
      }

      c9_f_j++;
      _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 5, 0);
    c9_f_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 4, 0);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 137U);
  for (c9_i31 = 0; c9_i31 < 3; c9_i31++) {
    c9_BodyForce[c9_i31] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 138U);
  for (c9_i32 = 0; c9_i32 < 3; c9_i32++) {
    c9_BodyMoment[c9_i32] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 139U);
  for (c9_i33 = 0; c9_i33 < 3; c9_i33++) {
    c9_p_FK_total[c9_i33] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 140U);
  for (c9_i34 = 0; c9_i34 < 3; c9_i34++) {
    c9_p_FK_l_total[c9_i34] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 141U);
  c9_i = 1.0;
  c9_h_i = 0;
  while (c9_h_i < 1094) {
    c9_i = 1.0 + (real_T)c9_h_i;
    CV_EML_FOR(0, 1, 6, 1);
    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 142U);
    c9_A = (c9_STL[(int32_T)c9_i - 1] + c9_STL[(int32_T)c9_i + 1093]) + c9_STL
      [(int32_T)c9_i + 2187];
    c9_o_x = c9_A;
    c9_p_x = c9_o_x;
    c9_x_m = c9_p_x / 3.0;
    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 143U);
    c9_b_A = (c9_STL[(int32_T)c9_i + 3281] + c9_STL[(int32_T)c9_i + 4375]) +
      c9_STL[(int32_T)c9_i + 5469];
    c9_q_x = c9_b_A;
    c9_r_x = c9_q_x;
    c9_y_m = c9_r_x / 3.0;
    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 144U);
    c9_c_A = (c9_STL[(int32_T)c9_i + 6563] + c9_STL[(int32_T)c9_i + 7657]) +
      c9_STL[(int32_T)c9_i + 8751];
    c9_s_x = c9_c_A;
    c9_t_x = c9_s_x;
    c9_z_m = c9_t_x / 3.0;
    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 145U);
    c9_r_m[0] = c9_x_m;
    c9_r_m[1] = c9_y_m;
    c9_r_m[2] = c9_z_m;
    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 147U);
    c9_r_a[0] = c9_STL[(int32_T)c9_i - 1];
    c9_r_a[1] = c9_STL[(int32_T)c9_i + 3281];
    c9_r_a[2] = c9_STL[(int32_T)c9_i + 6563];
    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 148U);
    c9_r_b[0] = c9_STL[(int32_T)c9_i + 1093];
    c9_r_b[1] = c9_STL[(int32_T)c9_i + 4375];
    c9_r_b[2] = c9_STL[(int32_T)c9_i + 7657];
    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 149U);
    c9_r_c[0] = c9_STL[(int32_T)c9_i + 2187];
    c9_r_c[1] = c9_STL[(int32_T)c9_i + 5469];
    c9_r_c[2] = c9_STL[(int32_T)c9_i + 8751];
    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 151U);
    for (c9_i35 = 0; c9_i35 < 3; c9_i35++) {
      c9_AB[c9_i35] = c9_r_b[c9_i35] - c9_r_a[c9_i35];
    }

    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 152U);
    for (c9_i36 = 0; c9_i36 < 3; c9_i36++) {
      c9_AC[c9_i36] = c9_r_c[c9_i36] - c9_r_a[c9_i36];
    }

    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 153U);
    for (c9_i37 = 0; c9_i37 < 3; c9_i37++) {
      c9_b_AC[c9_i37] = c9_AC[c9_i37];
    }

    for (c9_i38 = 0; c9_i38 < 3; c9_i38++) {
      c9_b_AB[c9_i38] = c9_AB[c9_i38];
    }

    c9_cross(chartInstance, c9_b_AC, c9_b_AB, c9_dv6);
    for (c9_i39 = 0; c9_i39 < 3; c9_i39++) {
      c9_CP[c9_i39] = c9_dv6[c9_i39];
    }

    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 154U);
    for (c9_i40 = 0; c9_i40 < 3; c9_i40++) {
      c9_qb_b[c9_i40] = c9_CP[c9_i40];
    }

    for (c9_i41 = 0; c9_i41 < 3; c9_i41++) {
      c9_area[c9_i41] = 0.5 * c9_qb_b[c9_i41];
    }

    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 156U);
    c9_d_A = (c9_STL_l[(int32_T)c9_i - 1] + c9_STL_l[(int32_T)c9_i + 1093]) +
      c9_STL_l[(int32_T)c9_i + 2187];
    c9_u_x = c9_d_A;
    c9_v_x = c9_u_x;
    c9_x_m_l = c9_v_x / 3.0;
    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 157U);
    c9_e_A = (c9_STL_l[(int32_T)c9_i + 3281] + c9_STL_l[(int32_T)c9_i + 4375]) +
      c9_STL_l[(int32_T)c9_i + 5469];
    c9_w_x = c9_e_A;
    c9_x_x = c9_w_x;
    c9_y_m_l = c9_x_x / 3.0;
    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 158U);
    c9_f_A = (c9_STL_l[(int32_T)c9_i + 6563] + c9_STL_l[(int32_T)c9_i + 7657]) +
      c9_STL_l[(int32_T)c9_i + 8751];
    c9_y_x = c9_f_A;
    c9_ab_x = c9_y_x;
    c9_z_m_l = c9_ab_x / 3.0;
    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 159U);
    c9_r_m_l[0] = c9_x_m_l;
    c9_r_m_l[1] = c9_y_m_l;
    c9_r_m_l[2] = c9_z_m_l;
    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 161U);
    c9_r_a_l[0] = c9_STL_l[(int32_T)c9_i - 1];
    c9_r_a_l[1] = c9_STL_l[(int32_T)c9_i + 3281];
    c9_r_a_l[2] = c9_STL_l[(int32_T)c9_i + 6563];
    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 162U);
    c9_r_b_l[0] = c9_STL_l[(int32_T)c9_i + 1093];
    c9_r_b_l[1] = c9_STL_l[(int32_T)c9_i + 4375];
    c9_r_b_l[2] = c9_STL_l[(int32_T)c9_i + 7657];
    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 163U);
    c9_r_c_l[0] = c9_STL_l[(int32_T)c9_i + 2187];
    c9_r_c_l[1] = c9_STL_l[(int32_T)c9_i + 5469];
    c9_r_c_l[2] = c9_STL_l[(int32_T)c9_i + 8751];
    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 165U);
    for (c9_i42 = 0; c9_i42 < 3; c9_i42++) {
      c9_AB_l[c9_i42] = c9_r_b_l[c9_i42] - c9_r_a_l[c9_i42];
    }

    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 166U);
    for (c9_i43 = 0; c9_i43 < 3; c9_i43++) {
      c9_AC_l[c9_i43] = c9_r_c_l[c9_i43] - c9_r_a_l[c9_i43];
    }

    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 167U);
    for (c9_i44 = 0; c9_i44 < 3; c9_i44++) {
      c9_b_AC_l[c9_i44] = c9_AC_l[c9_i44];
    }

    for (c9_i45 = 0; c9_i45 < 3; c9_i45++) {
      c9_b_AB_l[c9_i45] = c9_AB_l[c9_i45];
    }

    c9_cross(chartInstance, c9_b_AC_l, c9_b_AB_l, c9_dv7);
    for (c9_i46 = 0; c9_i46 < 3; c9_i46++) {
      c9_CP_l[c9_i46] = c9_dv7[c9_i46];
    }

    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 168U);
    for (c9_i47 = 0; c9_i47 < 3; c9_i47++) {
      c9_qb_b[c9_i47] = c9_CP_l[c9_i47];
    }

    for (c9_i48 = 0; c9_i48 < 3; c9_i48++) {
      c9_area_l[c9_i48] = 0.5 * c9_qb_b[c9_i48];
    }

    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 170U);
    c9_g_A = (c9_psi[(int32_T)c9_i - 1] + c9_psi[(int32_T)c9_i + 1093]) +
      c9_psi[(int32_T)c9_i + 2187];
    c9_bb_x = c9_g_A;
    c9_cb_x = c9_bb_x;
    c9_yc_y = c9_cb_x / 3.0;
    c9_psi_avg_sizes[0] = 1;
    c9_psi_avg_sizes[1] = 1;
    c9_b_psi_avg = c9_psi_avg_sizes[0];
    c9_c_psi_avg = c9_psi_avg_sizes[1];
    c9_psi_avg_data[0] = c9_yc_y;
    _SFD_SYMBOL_SWITCH(15U, 53U);
    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 171U);
    c9_h_A = (c9_psi_l[(int32_T)c9_i - 1] + c9_psi_l[(int32_T)c9_i + 1093]) +
      c9_psi_l[(int32_T)c9_i + 2187];
    c9_db_x = c9_h_A;
    c9_eb_x = c9_db_x;
    c9_ad_y = c9_eb_x / 3.0;
    c9_psi_l_avg_sizes[0] = 1;
    c9_psi_l_avg_sizes[1] = 1;
    c9_b_psi_l_avg = c9_psi_l_avg_sizes[0];
    c9_c_psi_l_avg = c9_psi_l_avg_sizes[1];
    c9_psi_l_avg_data[0] = c9_ad_y;
    _SFD_SYMBOL_SWITCH(16U, 54U);
    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 173U);
    c9_pc_a = -c9_z_m;
    for (c9_i49 = 0; c9_i49 < 3; c9_i49++) {
      c9_qb_b[c9_i49] = c9_area[c9_i49];
    }

    for (c9_i50 = 0; c9_i50 < 3; c9_i50++) {
      c9_p_HS[c9_i50] = c9_pc_a * c9_qb_b[c9_i50];
    }

    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 174U);
    for (c9_i51 = 0; c9_i51 < 3; c9_i51++) {
      c9_qb_b[c9_i51] = c9_area[c9_i51];
    }

    c9_b_sizes[0] = 1;
    c9_b_sizes[1] = 1;
    c9_rb_b = c9_b_sizes[0];
    c9_sb_b = c9_b_sizes[1];
    c9_loop_ub = c9_psi_avg_sizes[0] * c9_psi_avg_sizes[1] - 1;
    for (c9_i52 = 0; c9_i52 <= c9_loop_ub; c9_i52++) {
      c9_b_data[c9_i52] = c9_psi_avg_data[c9_i52];
    }

    c9_y_sizes[0] = 3;
    c9_y_sizes[1] = 1;
    for (c9_i53 = 0; c9_i53 < 3; c9_i53++) {
      c9_y_data[c9_i53] = c9_qb_b[c9_i53] * c9_b_data[0];
    }

    c9_qc_a = c9_k;
    c9_b_sizes[0] = 1;
    c9_b_sizes[1] = 1;
    c9_tb_b = c9_b_sizes[0];
    c9_ub_b = c9_b_sizes[1];
    c9_b_loop_ub = c9_psi_avg_sizes[0] * c9_psi_avg_sizes[1] - 1;
    for (c9_i54 = 0; c9_i54 <= c9_b_loop_ub; c9_i54++) {
      c9_b_data[c9_i54] = (c9_z_m + c9_psi_avg_data[c9_i54]) + c9_d;
    }

    c9_b_sizes[0] = 1;
    c9_b_sizes[1] = 1;
    c9_vb_b = c9_b_sizes[0];
    c9_wb_b = c9_b_sizes[1];
    c9_xb_b = c9_b_sizes[0];
    c9_yb_b = c9_b_sizes[1];
    c9_c_loop_ub = c9_xb_b * c9_yb_b - 1;
    for (c9_i55 = 0; c9_i55 <= c9_c_loop_ub; c9_i55++) {
      c9_b_data[c9_i55] *= c9_qc_a;
    }

    c9_b_cosh(chartInstance, c9_b_data, c9_b_sizes);
    c9_b_y_sizes[0] = 3;
    c9_b_y_sizes[1] = 1;
    for (c9_i56 = 0; c9_i56 < 3; c9_i56++) {
      c9_b_y_data[c9_i56] = c9_y_data[c9_i56] * c9_b_data[0];
    }

    c9_rc_a = c9_k;
    c9_ac_b = c9_d;
    c9_bd_y = c9_rc_a * c9_ac_b;
    c9_fb_x = c9_bd_y;
    c9_gb_x = c9_fb_x;
    c9_gb_x = muDoubleScalarCosh(c9_gb_x);
    c9_B = c9_gb_x;
    c9_cd_y = c9_B;
    c9_dd_y = c9_cd_y;
    c9_p_FK_sizes[0] = 3;
    c9_p_FK_sizes[1] = 1;
    c9_p_FK = c9_p_FK_sizes[0];
    c9_b_p_FK = c9_p_FK_sizes[1];
    c9_d_loop_ub = c9_b_y_sizes[0] * c9_b_y_sizes[1] - 1;
    for (c9_i57 = 0; c9_i57 <= c9_d_loop_ub; c9_i57++) {
      c9_p_FK_data[c9_i57] = c9_b_y_data[c9_i57] / c9_dd_y;
    }

    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 175U);
    for (c9_i58 = 0; c9_i58 < 3; c9_i58++) {
      c9_qb_b[c9_i58] = c9_area_l[c9_i58];
    }

    c9_b_sizes[0] = 1;
    c9_b_sizes[1] = 1;
    c9_bc_b = c9_b_sizes[0];
    c9_cc_b = c9_b_sizes[1];
    c9_e_loop_ub = c9_psi_l_avg_sizes[0] * c9_psi_l_avg_sizes[1] - 1;
    for (c9_i59 = 0; c9_i59 <= c9_e_loop_ub; c9_i59++) {
      c9_b_data[c9_i59] = c9_psi_l_avg_data[c9_i59];
    }

    c9_y_sizes[0] = 3;
    c9_y_sizes[1] = 1;
    for (c9_i60 = 0; c9_i60 < 3; c9_i60++) {
      c9_y_data[c9_i60] = c9_qb_b[c9_i60] * c9_b_data[0];
    }

    c9_sc_a = c9_k;
    c9_b_sizes[0] = 1;
    c9_b_sizes[1] = 1;
    c9_dc_b = c9_b_sizes[0];
    c9_ec_b = c9_b_sizes[1];
    c9_f_loop_ub = c9_psi_l_avg_sizes[0] * c9_psi_l_avg_sizes[1] - 1;
    for (c9_i61 = 0; c9_i61 <= c9_f_loop_ub; c9_i61++) {
      c9_b_data[c9_i61] = (c9_z_m_l + c9_psi_l_avg_data[c9_i61]) + c9_d;
    }

    c9_b_sizes[0] = 1;
    c9_b_sizes[1] = 1;
    c9_fc_b = c9_b_sizes[0];
    c9_gc_b = c9_b_sizes[1];
    c9_hc_b = c9_b_sizes[0];
    c9_ic_b = c9_b_sizes[1];
    c9_g_loop_ub = c9_hc_b * c9_ic_b - 1;
    for (c9_i62 = 0; c9_i62 <= c9_g_loop_ub; c9_i62++) {
      c9_b_data[c9_i62] *= c9_sc_a;
    }

    c9_b_cosh(chartInstance, c9_b_data, c9_b_sizes);
    c9_b_y_sizes[0] = 3;
    c9_b_y_sizes[1] = 1;
    for (c9_i63 = 0; c9_i63 < 3; c9_i63++) {
      c9_b_y_data[c9_i63] = c9_y_data[c9_i63] * c9_b_data[0];
    }

    c9_tc_a = c9_k;
    c9_jc_b = c9_d;
    c9_ed_y = c9_tc_a * c9_jc_b;
    c9_hb_x = c9_ed_y;
    c9_ib_x = c9_hb_x;
    c9_ib_x = muDoubleScalarCosh(c9_ib_x);
    c9_b_B = c9_ib_x;
    c9_fd_y = c9_b_B;
    c9_gd_y = c9_fd_y;
    c9_p_FK_l_sizes[0] = 3;
    c9_p_FK_l_sizes[1] = 1;
    c9_p_FK_l = c9_p_FK_l_sizes[0];
    c9_b_p_FK_l = c9_p_FK_l_sizes[1];
    c9_h_loop_ub = c9_b_y_sizes[0] * c9_b_y_sizes[1] - 1;
    for (c9_i64 = 0; c9_i64 <= c9_h_loop_ub; c9_i64++) {
      c9_p_FK_l_data[c9_i64] = c9_b_y_data[c9_i64] / c9_gd_y;
    }

    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 176U);
    for (c9_i65 = 0; c9_i65 < 3; c9_i65++) {
      c9_p_total[c9_i65] = (c9_p_HS[c9_i65] + c9_p_FK_data[c9_i65]) -
        c9_p_FK_l_data[c9_i65];
    }

    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 178U);
    for (c9_i66 = 0; c9_i66 < 3; c9_i66++) {
      c9_BodyForce[c9_i66] += c9_p_total[c9_i66];
    }

    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 179U);
    for (c9_i67 = 0; c9_i67 < 3; c9_i67++) {
      c9_b_r_m[c9_i67] = c9_r_m[c9_i67];
    }

    for (c9_i68 = 0; c9_i68 < 3; c9_i68++) {
      c9_b_p_total[c9_i68] = c9_p_total[c9_i68];
    }

    c9_cross(chartInstance, c9_b_r_m, c9_b_p_total, c9_dv8);
    for (c9_i69 = 0; c9_i69 < 3; c9_i69++) {
      c9_PanelMoment[c9_i69] = c9_dv8[c9_i69];
    }

    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 180U);
    for (c9_i70 = 0; c9_i70 < 3; c9_i70++) {
      c9_BodyMoment[c9_i70] += c9_PanelMoment[c9_i70];
    }

    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 182U);
    for (c9_i71 = 0; c9_i71 < 3; c9_i71++) {
      c9_p_FK_total[c9_i71] += c9_p_FK_data[c9_i71];
    }

    _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, 183U);
    for (c9_i72 = 0; c9_i72 < 3; c9_i72++) {
      c9_p_FK_l_total[c9_i72] += c9_p_FK_l_data[c9_i72];
    }

    c9_h_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 6, 0);
  _SFD_EML_CALL(0U, chartInstance->c9_sfEvent, -183);
  _SFD_SYMBOL_SCOPE_POP();
  for (c9_i73 = 0; c9_i73 < 3; c9_i73++) {
    (*c9_b_BodyForce)[c9_i73] = c9_BodyForce[c9_i73];
  }

  for (c9_i74 = 0; c9_i74 < 3; c9_i74++) {
    (*c9_b_BodyMoment)[c9_i74] = c9_BodyMoment[c9_i74];
  }

  *c9_b_psi_m = c9_psi_m;
  for (c9_i75 = 0; c9_i75 < 3; c9_i75++) {
    (*c9_b_p_FK_total)[c9_i75] = c9_p_FK_total[c9_i75];
  }

  for (c9_i76 = 0; c9_i76 < 3; c9_i76++) {
    (*c9_b_p_FK_l_total)[c9_i76] = c9_p_FK_l_total[c9_i76];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c9_sfEvent);
}

static void initSimStructsc9_WEC_Sim_Driver(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
}

static void registerMessagesc9_WEC_Sim_Driver(SFc9_WEC_Sim_DriverInstanceStruct *
  chartInstance)
{
}

static void init_script_number_translation(uint32_T c9_machineNumber, uint32_T
  c9_chartNumber)
{
}

static const mxArray *c9_sf_marshallOut(void *chartInstanceVoid, void *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_i77;
  real_T c9_b_inData[3];
  int32_T c9_i78;
  real_T c9_u[3];
  const mxArray *c9_y = NULL;
  SFc9_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc9_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  for (c9_i77 = 0; c9_i77 < 3; c9_i77++) {
    c9_b_inData[c9_i77] = (*(real_T (*)[3])c9_inData)[c9_i77];
  }

  for (c9_i78 = 0; c9_i78 < 3; c9_i78++) {
    c9_u[c9_i78] = c9_b_inData[c9_i78];
  }

  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", c9_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static void c9_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct *chartInstance,
  const mxArray *c9_p_FK_l_total, const char_T *c9_identifier, real_T c9_y[3])
{
  emlrtMsgIdentifier c9_thisId;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_p_FK_l_total), &c9_thisId,
                        c9_y);
  sf_mex_destroy(&c9_p_FK_l_total);
}

static void c9_b_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId,
  real_T c9_y[3])
{
  real_T c9_dv9[3];
  int32_T c9_i79;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), c9_dv9, 1, 0, 0U, 1, 0U, 1, 3);
  for (c9_i79 = 0; c9_i79 < 3; c9_i79++) {
    c9_y[c9_i79] = c9_dv9[c9_i79];
  }

  sf_mex_destroy(&c9_u);
}

static void c9_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_p_FK_l_total;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  real_T c9_y[3];
  int32_T c9_i80;
  SFc9_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc9_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c9_p_FK_l_total = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_p_FK_l_total), &c9_thisId,
                        c9_y);
  sf_mex_destroy(&c9_p_FK_l_total);
  for (c9_i80 = 0; c9_i80 < 3; c9_i80++) {
    (*(real_T (*)[3])c9_outData)[c9_i80] = c9_y[c9_i80];
  }

  sf_mex_destroy(&c9_mxArrayInData);
}

static const mxArray *c9_b_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  real_T c9_u;
  const mxArray *c9_y = NULL;
  SFc9_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc9_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_u = *(real_T *)c9_inData;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", &c9_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static real_T c9_c_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_psi_m, const char_T *c9_identifier)
{
  real_T c9_y;
  emlrtMsgIdentifier c9_thisId;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_psi_m), &c9_thisId);
  sf_mex_destroy(&c9_psi_m);
  return c9_y;
}

static real_T c9_d_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  real_T c9_y;
  real_T c9_d0;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_d0, 1, 0, 0U, 0, 0U, 0);
  c9_y = c9_d0;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void c9_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_psi_m;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  real_T c9_y;
  SFc9_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc9_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c9_psi_m = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_psi_m), &c9_thisId);
  sf_mex_destroy(&c9_psi_m);
  *(real_T *)c9_outData = c9_y;
  sf_mex_destroy(&c9_mxArrayInData);
}

static const mxArray *c9_c_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_i81;
  real_T c9_b_inData[4];
  int32_T c9_i82;
  real_T c9_u[4];
  const mxArray *c9_y = NULL;
  SFc9_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc9_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  for (c9_i81 = 0; c9_i81 < 4; c9_i81++) {
    c9_b_inData[c9_i81] = (*(real_T (*)[4])c9_inData)[c9_i81];
  }

  for (c9_i82 = 0; c9_i82 < 4; c9_i82++) {
    c9_u[c9_i82] = c9_b_inData[c9_i82];
  }

  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", c9_u, 0, 0U, 1U, 0U, 2, 4, 1), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static const mxArray *c9_d_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_i83;
  real_T c9_b_inData[6];
  int32_T c9_i84;
  real_T c9_u[6];
  const mxArray *c9_y = NULL;
  SFc9_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc9_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  for (c9_i83 = 0; c9_i83 < 6; c9_i83++) {
    c9_b_inData[c9_i83] = (*(real_T (*)[6])c9_inData)[c9_i83];
  }

  for (c9_i84 = 0; c9_i84 < 6; c9_i84++) {
    c9_u[c9_i84] = c9_b_inData[c9_i84];
  }

  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", c9_u, 0, 0U, 1U, 0U, 1, 6), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static const mxArray *c9_e_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_i85;
  int32_T c9_i86;
  int32_T c9_i87;
  int32_T c9_i88;
  int32_T c9_i89;
  real_T c9_b_inData[9846];
  int32_T c9_i90;
  int32_T c9_i91;
  int32_T c9_i92;
  int32_T c9_i93;
  int32_T c9_i94;
  real_T c9_u[9846];
  const mxArray *c9_y = NULL;
  SFc9_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc9_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_i85 = 0;
  for (c9_i86 = 0; c9_i86 < 3; c9_i86++) {
    c9_i87 = 0;
    for (c9_i88 = 0; c9_i88 < 3; c9_i88++) {
      for (c9_i89 = 0; c9_i89 < 1094; c9_i89++) {
        c9_b_inData[(c9_i89 + c9_i87) + c9_i85] = (*(real_T (*)[9846])c9_inData)
          [(c9_i89 + c9_i87) + c9_i85];
      }

      c9_i87 += 1094;
    }

    c9_i85 += 3282;
  }

  c9_i90 = 0;
  for (c9_i91 = 0; c9_i91 < 3; c9_i91++) {
    c9_i92 = 0;
    for (c9_i93 = 0; c9_i93 < 3; c9_i93++) {
      for (c9_i94 = 0; c9_i94 < 1094; c9_i94++) {
        c9_u[(c9_i94 + c9_i92) + c9_i90] = c9_b_inData[(c9_i94 + c9_i92) +
          c9_i90];
      }

      c9_i92 += 1094;
    }

    c9_i90 += 3282;
  }

  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", c9_u, 0, 0U, 1U, 0U, 3, 1094, 3, 3),
                FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static const mxArray *c9_f_sf_marshallOut(void *chartInstanceVoid, real_T
  c9_inData_data[1], int32_T c9_inData_sizes[2])
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_b_inData_sizes[2];
  real_T c9_b_inData_data[1];
  int32_T c9_u_sizes[2];
  real_T c9_u_data[1];
  const mxArray *c9_y = NULL;
  SFc9_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc9_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_b_inData_sizes[0] = 1;
  c9_b_inData_sizes[1] = 1;
  c9_b_inData_data[0] = c9_inData_data[0];
  c9_u_sizes[0] = 1;
  c9_u_sizes[1] = 1;
  c9_u_data[0] = c9_b_inData_data[0];
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", c9_u_data, 0, 0U, 1U, 0U, 2,
    c9_u_sizes[0], c9_u_sizes[1]), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static void c9_e_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId,
  real_T c9_y_data[1], int32_T c9_y_sizes[2])
{
  int32_T c9_i95;
  uint32_T c9_uv0[2];
  int32_T c9_i96;
  boolean_T c9_bv0[2];
  int32_T c9_tmp_sizes[2];
  real_T c9_tmp_data[1];
  int32_T c9_y;
  int32_T c9_b_y;
  int32_T c9_loop_ub;
  int32_T c9_i97;
  for (c9_i95 = 0; c9_i95 < 2; c9_i95++) {
    c9_uv0[c9_i95] = 1U;
  }

  for (c9_i96 = 0; c9_i96 < 2; c9_i96++) {
    c9_bv0[c9_i96] = FALSE;
  }

  sf_mex_import_vs(c9_parentId, sf_mex_dup(c9_u), c9_tmp_data, 1, 0, 0U, 1, 0U,
                   2, c9_bv0, c9_uv0, c9_tmp_sizes);
  c9_y_sizes[0] = 1;
  c9_y_sizes[1] = 1;
  c9_y = c9_y_sizes[0];
  c9_b_y = c9_y_sizes[1];
  c9_loop_ub = c9_tmp_sizes[0] * c9_tmp_sizes[1] - 1;
  for (c9_i97 = 0; c9_i97 <= c9_loop_ub; c9_i97++) {
    c9_y_data[c9_i97] = c9_tmp_data[c9_i97];
  }

  sf_mex_destroy(&c9_u);
}

static void c9_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, real_T c9_outData_data[1],
  int32_T c9_outData_sizes[2])
{
  const mxArray *c9_psi_l_avg;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  int32_T c9_y_sizes[2];
  real_T c9_y_data[1];
  SFc9_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc9_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c9_psi_l_avg = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_psi_l_avg), &c9_thisId,
                        c9_y_data, c9_y_sizes);
  sf_mex_destroy(&c9_psi_l_avg);
  c9_outData_sizes[0] = 1;
  c9_outData_sizes[1] = 1;
  c9_outData_data[0] = c9_y_data[0];
  sf_mex_destroy(&c9_mxArrayInData);
}

static const mxArray *c9_g_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_i98;
  real_T c9_b_inData[3];
  int32_T c9_i99;
  real_T c9_u[3];
  const mxArray *c9_y = NULL;
  SFc9_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc9_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  for (c9_i98 = 0; c9_i98 < 3; c9_i98++) {
    c9_b_inData[c9_i98] = (*(real_T (*)[3])c9_inData)[c9_i98];
  }

  for (c9_i99 = 0; c9_i99 < 3; c9_i99++) {
    c9_u[c9_i99] = c9_b_inData[c9_i99];
  }

  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", c9_u, 0, 0U, 1U, 0U, 2, 3, 1), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static void c9_f_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId,
  real_T c9_y[3])
{
  real_T c9_dv10[3];
  int32_T c9_i100;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), c9_dv10, 1, 0, 0U, 1, 0U, 2, 3, 1);
  for (c9_i100 = 0; c9_i100 < 3; c9_i100++) {
    c9_y[c9_i100] = c9_dv10[c9_i100];
  }

  sf_mex_destroy(&c9_u);
}

static void c9_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_p_total;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  real_T c9_y[3];
  int32_T c9_i101;
  SFc9_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc9_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c9_p_total = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_p_total), &c9_thisId, c9_y);
  sf_mex_destroy(&c9_p_total);
  for (c9_i101 = 0; c9_i101 < 3; c9_i101++) {
    (*(real_T (*)[3])c9_outData)[c9_i101] = c9_y[c9_i101];
  }

  sf_mex_destroy(&c9_mxArrayInData);
}

static const mxArray *c9_h_sf_marshallOut(void *chartInstanceVoid, real_T
  c9_inData_data[3], int32_T c9_inData_sizes[2])
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_b_inData_sizes[2];
  int32_T c9_i102;
  real_T c9_b_inData_data[3];
  int32_T c9_u_sizes[2];
  int32_T c9_i103;
  real_T c9_u_data[3];
  const mxArray *c9_y = NULL;
  SFc9_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc9_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_b_inData_sizes[0] = 3;
  c9_b_inData_sizes[1] = 1;
  for (c9_i102 = 0; c9_i102 < 3; c9_i102++) {
    c9_b_inData_data[c9_i102] = c9_inData_data[c9_i102];
  }

  c9_u_sizes[0] = 3;
  c9_u_sizes[1] = 1;
  for (c9_i103 = 0; c9_i103 < 3; c9_i103++) {
    c9_u_data[c9_i103] = c9_b_inData_data[c9_i103];
  }

  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", c9_u_data, 0, 0U, 1U, 0U, 2,
    c9_u_sizes[0], c9_u_sizes[1]), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static void c9_g_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId,
  real_T c9_y_data[3], int32_T c9_y_sizes[2])
{
  int32_T c9_i104;
  static uint32_T c9_uv1[2] = { 3U, 1U };

  uint32_T c9_uv2[2];
  int32_T c9_i105;
  boolean_T c9_bv1[2];
  int32_T c9_tmp_sizes[2];
  real_T c9_tmp_data[3];
  int32_T c9_y;
  int32_T c9_b_y;
  int32_T c9_loop_ub;
  int32_T c9_i106;
  for (c9_i104 = 0; c9_i104 < 2; c9_i104++) {
    c9_uv2[c9_i104] = c9_uv1[c9_i104];
  }

  for (c9_i105 = 0; c9_i105 < 2; c9_i105++) {
    c9_bv1[c9_i105] = FALSE;
  }

  sf_mex_import_vs(c9_parentId, sf_mex_dup(c9_u), c9_tmp_data, 1, 0, 0U, 1, 0U,
                   2, c9_bv1, c9_uv2, c9_tmp_sizes);
  c9_y_sizes[0] = 3;
  c9_y_sizes[1] = 1;
  c9_y = c9_y_sizes[0];
  c9_b_y = c9_y_sizes[1];
  c9_loop_ub = c9_tmp_sizes[0] * c9_tmp_sizes[1] - 1;
  for (c9_i106 = 0; c9_i106 <= c9_loop_ub; c9_i106++) {
    c9_y_data[c9_i106] = c9_tmp_data[c9_i106];
  }

  sf_mex_destroy(&c9_u);
}

static void c9_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, real_T c9_outData_data[3],
  int32_T c9_outData_sizes[2])
{
  const mxArray *c9_p_FK_l;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  int32_T c9_y_sizes[2];
  real_T c9_y_data[3];
  int32_T c9_i107;
  SFc9_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc9_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c9_p_FK_l = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_p_FK_l), &c9_thisId,
                        c9_y_data, c9_y_sizes);
  sf_mex_destroy(&c9_p_FK_l);
  c9_outData_sizes[0] = 3;
  c9_outData_sizes[1] = 1;
  for (c9_i107 = 0; c9_i107 < 3; c9_i107++) {
    c9_outData_data[c9_i107] = c9_y_data[c9_i107];
  }

  sf_mex_destroy(&c9_mxArrayInData);
}

static const mxArray *c9_i_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_i108;
  real_T c9_b_inData[3];
  int32_T c9_i109;
  real_T c9_u[3];
  const mxArray *c9_y = NULL;
  SFc9_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc9_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  for (c9_i108 = 0; c9_i108 < 3; c9_i108++) {
    c9_b_inData[c9_i108] = (*(real_T (*)[3])c9_inData)[c9_i108];
  }

  for (c9_i109 = 0; c9_i109 < 3; c9_i109++) {
    c9_u[c9_i109] = c9_b_inData[c9_i109];
  }

  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", c9_u, 0, 0U, 1U, 0U, 2, 1, 3), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static void c9_h_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId,
  real_T c9_y[3])
{
  real_T c9_dv11[3];
  int32_T c9_i110;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), c9_dv11, 1, 0, 0U, 1, 0U, 2, 1, 3);
  for (c9_i110 = 0; c9_i110 < 3; c9_i110++) {
    c9_y[c9_i110] = c9_dv11[c9_i110];
  }

  sf_mex_destroy(&c9_u);
}

static void c9_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_q;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  real_T c9_y[3];
  int32_T c9_i111;
  SFc9_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc9_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c9_q = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_q), &c9_thisId, c9_y);
  sf_mex_destroy(&c9_q);
  for (c9_i111 = 0; c9_i111 < 3; c9_i111++) {
    (*(real_T (*)[3])c9_outData)[c9_i111] = c9_y[c9_i111];
  }

  sf_mex_destroy(&c9_mxArrayInData);
}

static void c9_i_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId,
  real_T c9_y[9846])
{
  real_T c9_dv12[9846];
  int32_T c9_i112;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), c9_dv12, 1, 0, 0U, 1, 0U, 3, 1094,
                3, 3);
  for (c9_i112 = 0; c9_i112 < 9846; c9_i112++) {
    c9_y[c9_i112] = c9_dv12[c9_i112];
  }

  sf_mex_destroy(&c9_u);
}

static void c9_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_STL_l;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  real_T c9_y[9846];
  int32_T c9_i113;
  int32_T c9_i114;
  int32_T c9_i115;
  int32_T c9_i116;
  int32_T c9_i117;
  SFc9_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc9_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c9_STL_l = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_STL_l), &c9_thisId, c9_y);
  sf_mex_destroy(&c9_STL_l);
  c9_i113 = 0;
  for (c9_i114 = 0; c9_i114 < 3; c9_i114++) {
    c9_i115 = 0;
    for (c9_i116 = 0; c9_i116 < 3; c9_i116++) {
      for (c9_i117 = 0; c9_i117 < 1094; c9_i117++) {
        (*(real_T (*)[9846])c9_outData)[(c9_i117 + c9_i115) + c9_i113] = c9_y
          [(c9_i117 + c9_i115) + c9_i113];
      }

      c9_i115 += 1094;
    }

    c9_i113 += 3282;
  }

  sf_mex_destroy(&c9_mxArrayInData);
}

static const mxArray *c9_j_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_i118;
  int32_T c9_i119;
  int32_T c9_i120;
  real_T c9_b_inData[3282];
  int32_T c9_i121;
  int32_T c9_i122;
  int32_T c9_i123;
  real_T c9_u[3282];
  const mxArray *c9_y = NULL;
  SFc9_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc9_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_i118 = 0;
  for (c9_i119 = 0; c9_i119 < 3; c9_i119++) {
    for (c9_i120 = 0; c9_i120 < 1094; c9_i120++) {
      c9_b_inData[c9_i120 + c9_i118] = (*(real_T (*)[3282])c9_inData)[c9_i120 +
        c9_i118];
    }

    c9_i118 += 1094;
  }

  c9_i121 = 0;
  for (c9_i122 = 0; c9_i122 < 3; c9_i122++) {
    for (c9_i123 = 0; c9_i123 < 1094; c9_i123++) {
      c9_u[c9_i123 + c9_i121] = c9_b_inData[c9_i123 + c9_i121];
    }

    c9_i121 += 1094;
  }

  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", c9_u, 0, 0U, 1U, 0U, 2, 1094, 3),
                FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static void c9_j_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId,
  real_T c9_y[3282])
{
  real_T c9_dv13[3282];
  int32_T c9_i124;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), c9_dv13, 1, 0, 0U, 1, 0U, 2, 1094,
                3);
  for (c9_i124 = 0; c9_i124 < 3282; c9_i124++) {
    c9_y[c9_i124] = c9_dv13[c9_i124];
  }

  sf_mex_destroy(&c9_u);
}

static void c9_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_psi_l_avg;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  real_T c9_y[3282];
  int32_T c9_i125;
  int32_T c9_i126;
  int32_T c9_i127;
  SFc9_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc9_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c9_psi_l_avg = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_psi_l_avg), &c9_thisId,
                        c9_y);
  sf_mex_destroy(&c9_psi_l_avg);
  c9_i125 = 0;
  for (c9_i126 = 0; c9_i126 < 3; c9_i126++) {
    for (c9_i127 = 0; c9_i127 < 1094; c9_i127++) {
      (*(real_T (*)[3282])c9_outData)[c9_i127 + c9_i125] = c9_y[c9_i127 +
        c9_i125];
    }

    c9_i125 += 1094;
  }

  sf_mex_destroy(&c9_mxArrayInData);
}

const mxArray *sf_c9_WEC_Sim_Driver_get_eml_resolved_functions_info(void)
{
  const mxArray *c9_nameCaptureInfo;
  c9_ResolvedFunctionInfo c9_info[31];
  const mxArray *c9_m0 = NULL;
  int32_T c9_i128;
  c9_ResolvedFunctionInfo *c9_r0;
  c9_nameCaptureInfo = NULL;
  c9_nameCaptureInfo = NULL;
  c9_info_helper(c9_info);
  sf_mex_assign(&c9_m0, sf_mex_createstruct("nameCaptureInfo", 1, 31), FALSE);
  for (c9_i128 = 0; c9_i128 < 31; c9_i128++) {
    c9_r0 = &c9_info[c9_i128];
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", c9_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c9_r0->context)), "context", "nameCaptureInfo",
                    c9_i128);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", c9_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c9_r0->name)), "name", "nameCaptureInfo", c9_i128);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", c9_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c9_r0->dominantType)), "dominantType",
                    "nameCaptureInfo", c9_i128);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", c9_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c9_r0->resolved)), "resolved", "nameCaptureInfo",
                    c9_i128);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", &c9_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c9_i128);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", &c9_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c9_i128);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", &c9_r0->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c9_i128);
    sf_mex_addfield(c9_m0, sf_mex_create("nameCaptureInfo", &c9_r0->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c9_i128);
  }

  sf_mex_assign(&c9_nameCaptureInfo, c9_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c9_nameCaptureInfo);
  return c9_nameCaptureInfo;
}

static void c9_info_helper(c9_ResolvedFunctionInfo c9_info[31])
{
  c9_info[0].context = "";
  c9_info[0].name = "mtimes";
  c9_info[0].dominantType = "double";
  c9_info[0].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c9_info[0].fileTimeLo = 1289548492U;
  c9_info[0].fileTimeHi = 0U;
  c9_info[0].mFileTimeLo = 0U;
  c9_info[0].mFileTimeHi = 0U;
  c9_info[1].context = "";
  c9_info[1].name = "cos";
  c9_info[1].dominantType = "double";
  c9_info[1].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c9_info[1].fileTimeLo = 1343859172U;
  c9_info[1].fileTimeHi = 0U;
  c9_info[1].mFileTimeLo = 0U;
  c9_info[1].mFileTimeHi = 0U;
  c9_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c9_info[2].name = "eml_scalar_cos";
  c9_info[2].dominantType = "double";
  c9_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c9_info[2].fileTimeLo = 1286847522U;
  c9_info[2].fileTimeHi = 0U;
  c9_info[2].mFileTimeLo = 0U;
  c9_info[2].mFileTimeHi = 0U;
  c9_info[3].context = "";
  c9_info[3].name = "sin";
  c9_info[3].dominantType = "double";
  c9_info[3].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c9_info[3].fileTimeLo = 1343859186U;
  c9_info[3].fileTimeHi = 0U;
  c9_info[3].mFileTimeLo = 0U;
  c9_info[3].mFileTimeHi = 0U;
  c9_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c9_info[4].name = "eml_scalar_sin";
  c9_info[4].dominantType = "double";
  c9_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c9_info[4].fileTimeLo = 1286847536U;
  c9_info[4].fileTimeHi = 0U;
  c9_info[4].mFileTimeLo = 0U;
  c9_info[4].mFileTimeHi = 0U;
  c9_info[5].context = "";
  c9_info[5].name = "mrdivide";
  c9_info[5].dominantType = "double";
  c9_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c9_info[5].fileTimeLo = 1357980348U;
  c9_info[5].fileTimeHi = 0U;
  c9_info[5].mFileTimeLo = 1319758766U;
  c9_info[5].mFileTimeHi = 0U;
  c9_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c9_info[6].name = "rdivide";
  c9_info[6].dominantType = "double";
  c9_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c9_info[6].fileTimeLo = 1346539188U;
  c9_info[6].fileTimeHi = 0U;
  c9_info[6].mFileTimeLo = 0U;
  c9_info[6].mFileTimeHi = 0U;
  c9_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c9_info[7].name = "eml_scalexp_compatible";
  c9_info[7].dominantType = "double";
  c9_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c9_info[7].fileTimeLo = 1286847596U;
  c9_info[7].fileTimeHi = 0U;
  c9_info[7].mFileTimeLo = 0U;
  c9_info[7].mFileTimeHi = 0U;
  c9_info[8].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c9_info[8].name = "eml_div";
  c9_info[8].dominantType = "double";
  c9_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c9_info[8].fileTimeLo = 1313376610U;
  c9_info[8].fileTimeHi = 0U;
  c9_info[8].mFileTimeLo = 0U;
  c9_info[8].mFileTimeHi = 0U;
  c9_info[9].context = "";
  c9_info[9].name = "cross";
  c9_info[9].dominantType = "double";
  c9_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c9_info[9].fileTimeLo = 1286847642U;
  c9_info[9].fileTimeHi = 0U;
  c9_info[9].mFileTimeLo = 0U;
  c9_info[9].mFileTimeHi = 0U;
  c9_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c9_info[10].name = "mtimes";
  c9_info[10].dominantType = "double";
  c9_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c9_info[10].fileTimeLo = 1289548492U;
  c9_info[10].fileTimeHi = 0U;
  c9_info[10].mFileTimeLo = 0U;
  c9_info[10].mFileTimeHi = 0U;
  c9_info[11].context = "";
  c9_info[11].name = "cosh";
  c9_info[11].dominantType = "double";
  c9_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cosh.m";
  c9_info[11].fileTimeLo = 1343859174U;
  c9_info[11].fileTimeHi = 0U;
  c9_info[11].mFileTimeLo = 0U;
  c9_info[11].mFileTimeHi = 0U;
  c9_info[12].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cosh.m";
  c9_info[12].name = "eml_scalar_cosh";
  c9_info[12].dominantType = "double";
  c9_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cosh.m";
  c9_info[12].fileTimeLo = 1286847522U;
  c9_info[12].fileTimeHi = 0U;
  c9_info[12].mFileTimeLo = 0U;
  c9_info[12].mFileTimeHi = 0U;
  c9_info[13].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c9_info[13].name = "eml_index_class";
  c9_info[13].dominantType = "";
  c9_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[13].fileTimeLo = 1323199378U;
  c9_info[13].fileTimeHi = 0U;
  c9_info[13].mFileTimeLo = 0U;
  c9_info[13].mFileTimeHi = 0U;
  c9_info[14].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c9_info[14].name = "eml_scalar_eg";
  c9_info[14].dominantType = "double";
  c9_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c9_info[14].fileTimeLo = 1286847596U;
  c9_info[14].fileTimeHi = 0U;
  c9_info[14].mFileTimeLo = 0U;
  c9_info[14].mFileTimeHi = 0U;
  c9_info[15].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c9_info[15].name = "eml_xgemm";
  c9_info[15].dominantType = "char";
  c9_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c9_info[15].fileTimeLo = 1299105572U;
  c9_info[15].fileTimeHi = 0U;
  c9_info[15].mFileTimeLo = 0U;
  c9_info[15].mFileTimeHi = 0U;
  c9_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c9_info[16].name = "eml_blas_inline";
  c9_info[16].dominantType = "";
  c9_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c9_info[16].fileTimeLo = 1299105568U;
  c9_info[16].fileTimeHi = 0U;
  c9_info[16].mFileTimeLo = 0U;
  c9_info[16].mFileTimeHi = 0U;
  c9_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c9_info[17].name = "eml_index_class";
  c9_info[17].dominantType = "";
  c9_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[17].fileTimeLo = 1323199378U;
  c9_info[17].fileTimeHi = 0U;
  c9_info[17].mFileTimeLo = 0U;
  c9_info[17].mFileTimeHi = 0U;
  c9_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c9_info[18].name = "eml_scalar_eg";
  c9_info[18].dominantType = "double";
  c9_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c9_info[18].fileTimeLo = 1286847596U;
  c9_info[18].fileTimeHi = 0U;
  c9_info[18].mFileTimeLo = 0U;
  c9_info[18].mFileTimeHi = 0U;
  c9_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c9_info[19].name = "eml_refblas_xgemm";
  c9_info[19].dominantType = "char";
  c9_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c9_info[19].fileTimeLo = 1299105574U;
  c9_info[19].fileTimeHi = 0U;
  c9_info[19].mFileTimeLo = 0U;
  c9_info[19].mFileTimeHi = 0U;
  c9_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c9_info[20].name = "eml_index_minus";
  c9_info[20].dominantType = "double";
  c9_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c9_info[20].fileTimeLo = 1286847578U;
  c9_info[20].fileTimeHi = 0U;
  c9_info[20].mFileTimeLo = 0U;
  c9_info[20].mFileTimeHi = 0U;
  c9_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c9_info[21].name = "eml_index_class";
  c9_info[21].dominantType = "";
  c9_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[21].fileTimeLo = 1323199378U;
  c9_info[21].fileTimeHi = 0U;
  c9_info[21].mFileTimeLo = 0U;
  c9_info[21].mFileTimeHi = 0U;
  c9_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c9_info[22].name = "eml_index_class";
  c9_info[22].dominantType = "";
  c9_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[22].fileTimeLo = 1323199378U;
  c9_info[22].fileTimeHi = 0U;
  c9_info[22].mFileTimeLo = 0U;
  c9_info[22].mFileTimeHi = 0U;
  c9_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c9_info[23].name = "eml_scalar_eg";
  c9_info[23].dominantType = "double";
  c9_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c9_info[23].fileTimeLo = 1286847596U;
  c9_info[23].fileTimeHi = 0U;
  c9_info[23].mFileTimeLo = 0U;
  c9_info[23].mFileTimeHi = 0U;
  c9_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c9_info[24].name = "eml_index_times";
  c9_info[24].dominantType = "coder.internal.indexInt";
  c9_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c9_info[24].fileTimeLo = 1286847580U;
  c9_info[24].fileTimeHi = 0U;
  c9_info[24].mFileTimeLo = 0U;
  c9_info[24].mFileTimeHi = 0U;
  c9_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c9_info[25].name = "eml_index_class";
  c9_info[25].dominantType = "";
  c9_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[25].fileTimeLo = 1323199378U;
  c9_info[25].fileTimeHi = 0U;
  c9_info[25].mFileTimeLo = 0U;
  c9_info[25].mFileTimeHi = 0U;
  c9_info[26].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c9_info[26].name = "eml_index_plus";
  c9_info[26].dominantType = "coder.internal.indexInt";
  c9_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c9_info[26].fileTimeLo = 1286847578U;
  c9_info[26].fileTimeHi = 0U;
  c9_info[26].mFileTimeLo = 0U;
  c9_info[26].mFileTimeHi = 0U;
  c9_info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c9_info[27].name = "eml_index_class";
  c9_info[27].dominantType = "";
  c9_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c9_info[27].fileTimeLo = 1323199378U;
  c9_info[27].fileTimeHi = 0U;
  c9_info[27].mFileTimeLo = 0U;
  c9_info[27].mFileTimeHi = 0U;
  c9_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c9_info[28].name = "eml_int_forloop_overflow_check";
  c9_info[28].dominantType = "";
  c9_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c9_info[28].fileTimeLo = 1346539140U;
  c9_info[28].fileTimeHi = 0U;
  c9_info[28].mFileTimeLo = 0U;
  c9_info[28].mFileTimeHi = 0U;
  c9_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c9_info[29].name = "intmax";
  c9_info[29].dominantType = "char";
  c9_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c9_info[29].fileTimeLo = 1311284116U;
  c9_info[29].fileTimeHi = 0U;
  c9_info[29].mFileTimeLo = 0U;
  c9_info[29].mFileTimeHi = 0U;
  c9_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c9_info[30].name = "eml_index_plus";
  c9_info[30].dominantType = "double";
  c9_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c9_info[30].fileTimeLo = 1286847578U;
  c9_info[30].fileTimeHi = 0U;
  c9_info[30].mFileTimeLo = 0U;
  c9_info[30].mFileTimeHi = 0U;
}

static void c9_cross(SFc9_WEC_Sim_DriverInstanceStruct *chartInstance, real_T
                     c9_a[3], real_T c9_b[3], real_T c9_c[3])
{
  real_T c9_b_a;
  real_T c9_b_b;
  real_T c9_y;
  real_T c9_c_a;
  real_T c9_c_b;
  real_T c9_b_y;
  real_T c9_c1;
  real_T c9_d_a;
  real_T c9_d_b;
  real_T c9_c_y;
  real_T c9_e_a;
  real_T c9_e_b;
  real_T c9_d_y;
  real_T c9_c2;
  real_T c9_f_a;
  real_T c9_f_b;
  real_T c9_e_y;
  real_T c9_g_a;
  real_T c9_g_b;
  real_T c9_f_y;
  real_T c9_c3;
  c9_b_a = c9_a[1];
  c9_b_b = c9_b[2];
  c9_y = c9_b_a * c9_b_b;
  c9_c_a = c9_a[2];
  c9_c_b = c9_b[1];
  c9_b_y = c9_c_a * c9_c_b;
  c9_c1 = c9_y - c9_b_y;
  c9_d_a = c9_a[2];
  c9_d_b = c9_b[0];
  c9_c_y = c9_d_a * c9_d_b;
  c9_e_a = c9_a[0];
  c9_e_b = c9_b[2];
  c9_d_y = c9_e_a * c9_e_b;
  c9_c2 = c9_c_y - c9_d_y;
  c9_f_a = c9_a[0];
  c9_f_b = c9_b[1];
  c9_e_y = c9_f_a * c9_f_b;
  c9_g_a = c9_a[1];
  c9_g_b = c9_b[0];
  c9_f_y = c9_g_a * c9_g_b;
  c9_c3 = c9_e_y - c9_f_y;
  c9_c[0] = c9_c1;
  c9_c[1] = c9_c2;
  c9_c[2] = c9_c3;
}

static void c9_cosh(SFc9_WEC_Sim_DriverInstanceStruct *chartInstance, real_T
                    c9_x_data[1], int32_T c9_x_sizes[2], real_T c9_b_x_data[1],
                    int32_T c9_b_x_sizes[2])
{
  int32_T c9_x;
  int32_T c9_b_x;
  int32_T c9_loop_ub;
  int32_T c9_i129;
  c9_b_x_sizes[0] = 1;
  c9_b_x_sizes[1] = 1;
  c9_x = c9_b_x_sizes[0];
  c9_b_x = c9_b_x_sizes[1];
  c9_loop_ub = c9_x_sizes[0] * c9_x_sizes[1] - 1;
  for (c9_i129 = 0; c9_i129 <= c9_loop_ub; c9_i129++) {
    c9_b_x_data[c9_i129] = c9_x_data[c9_i129];
  }

  c9_b_cosh(chartInstance, c9_b_x_data, c9_b_x_sizes);
}

static const mxArray *c9_k_sf_marshallOut(void *chartInstanceVoid, void
  *c9_inData)
{
  const mxArray *c9_mxArrayOutData = NULL;
  int32_T c9_u;
  const mxArray *c9_y = NULL;
  SFc9_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc9_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c9_mxArrayOutData = NULL;
  c9_u = *(int32_T *)c9_inData;
  c9_y = NULL;
  sf_mex_assign(&c9_y, sf_mex_create("y", &c9_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c9_mxArrayOutData, c9_y, FALSE);
  return c9_mxArrayOutData;
}

static int32_T c9_k_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  int32_T c9_y;
  int32_T c9_i130;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_i130, 1, 6, 0U, 0, 0U, 0);
  c9_y = c9_i130;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void c9_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c9_mxArrayInData, const char_T *c9_varName, void *c9_outData)
{
  const mxArray *c9_b_sfEvent;
  const char_T *c9_identifier;
  emlrtMsgIdentifier c9_thisId;
  int32_T c9_y;
  SFc9_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc9_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c9_b_sfEvent = sf_mex_dup(c9_mxArrayInData);
  c9_identifier = c9_varName;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c9_b_sfEvent),
    &c9_thisId);
  sf_mex_destroy(&c9_b_sfEvent);
  *(int32_T *)c9_outData = c9_y;
  sf_mex_destroy(&c9_mxArrayInData);
}

static uint8_T c9_l_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_b_is_active_c9_WEC_Sim_Driver, const char_T *
  c9_identifier)
{
  uint8_T c9_y;
  emlrtMsgIdentifier c9_thisId;
  c9_thisId.fIdentifier = c9_identifier;
  c9_thisId.fParent = NULL;
  c9_y = c9_m_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c9_b_is_active_c9_WEC_Sim_Driver), &c9_thisId);
  sf_mex_destroy(&c9_b_is_active_c9_WEC_Sim_Driver);
  return c9_y;
}

static uint8_T c9_m_emlrt_marshallIn(SFc9_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c9_u, const emlrtMsgIdentifier *c9_parentId)
{
  uint8_T c9_y;
  uint8_T c9_u0;
  sf_mex_import(c9_parentId, sf_mex_dup(c9_u), &c9_u0, 1, 3, 0U, 0, 0U, 0);
  c9_y = c9_u0;
  sf_mex_destroy(&c9_u);
  return c9_y;
}

static void c9_b_cosh(SFc9_WEC_Sim_DriverInstanceStruct *chartInstance, real_T
                      c9_x_data[1], int32_T c9_x_sizes[2])
{
  int32_T c9_k;
  real_T c9_x;
  real_T c9_b_x;
  c9_k = 0;
  while (c9_k <= 0) {
    c9_x = c9_x_data[0];
    c9_b_x = c9_x;
    c9_b_x = muDoubleScalarCosh(c9_b_x);
    c9_x_data[0] = c9_b_x;
    c9_k = 1;
  }
}

static void init_dsm_address_info(SFc9_WEC_Sim_DriverInstanceStruct
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

void sf_c9_WEC_Sim_Driver_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1737074748U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1343968591U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1172020945U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(233238981U);
}

mxArray *sf_c9_WEC_Sim_Driver_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("KbfsvGp77lZmjDVQyKGY2D");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

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
      pr[0] = (double)(1);
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
      pr[0] = (double)(6);
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
      pr[0] = (double)(4);
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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,5,3,dataFields);

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
      pr[0] = (double)(1);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c9_WEC_Sim_Driver_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c9_WEC_Sim_Driver(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x6'type','srcId','name','auxInfo'{{M[1],M[5],T\"BodyForce\",},{M[1],M[10],T\"BodyMoment\",},{M[1],M[18],T\"p_FK_l_total\",},{M[1],M[17],T\"p_FK_total\",},{M[1],M[16],T\"psi_m\",},{M[8],M[0],T\"is_active_c9_WEC_Sim_Driver\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 6, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c9_WEC_Sim_Driver_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc9_WEC_Sim_DriverInstanceStruct *chartInstance;
    chartInstance = (SFc9_WEC_Sim_DriverInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _WEC_Sim_DriverMachineNumber_,
           9,
           1,
           1,
           9,
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
          _SFD_SET_DATA_PROPS(1,1,1,0,"t");
          _SFD_SET_DATA_PROPS(2,2,0,1,"BodyForce");
          _SFD_SET_DATA_PROPS(3,1,1,0,"Disp");
          _SFD_SET_DATA_PROPS(4,2,0,1,"BodyMoment");
          _SFD_SET_DATA_PROPS(5,1,1,0,"nonlinear_params");
          _SFD_SET_DATA_PROPS(6,2,0,1,"psi_m");
          _SFD_SET_DATA_PROPS(7,2,0,1,"p_FK_total");
          _SFD_SET_DATA_PROPS(8,2,0,1,"p_FK_l_total");
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
        _SFD_CV_INIT_EML(0,1,1,6,0,0,0,7,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,7172);
        _SFD_CV_INIT_EML_IF(0,1,0,1490,1503,-1,1539);
        _SFD_CV_INIT_EML_IF(0,1,1,1859,1878,-1,1929);
        _SFD_CV_INIT_EML_IF(0,1,2,1986,2003,-1,3161);
        _SFD_CV_INIT_EML_IF(0,1,3,3170,3187,-1,3251);
        _SFD_CV_INIT_EML_IF(0,1,4,3365,3382,4535,4679);
        _SFD_CV_INIT_EML_IF(0,1,5,4790,4808,-1,4849);
        _SFD_CV_INIT_EML_FOR(0,1,0,1294,1306,1655);
        _SFD_CV_INIT_EML_FOR(0,1,1,1310,1322,1651);
        _SFD_CV_INIT_EML_FOR(0,1,2,1726,1738,3263);
        _SFD_CV_INIT_EML_FOR(0,1,3,1742,1754,3259);
        _SFD_CV_INIT_EML_FOR(0,1,4,3265,3277,5039);
        _SFD_CV_INIT_EML_FOR(0,1,5,3281,3293,5035);
        _SFD_CV_INIT_EML_FOR(0,1,6,5182,5194,7100);
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
            1.0,0,0,(MexFcnForType)c9_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c9_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)
            c9_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)
            c9_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 4;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c9_b_sf_marshallOut,(MexInFcnForType)c9_b_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)
            c9_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c9_sf_marshallOut,(MexInFcnForType)
            c9_sf_marshallIn);
        }

        {
          real_T *c9_t;
          real_T *c9_psi_m;
          real_T (*c9_STL)[9846];
          real_T (*c9_BodyForce)[3];
          real_T (*c9_Disp)[6];
          real_T (*c9_BodyMoment)[3];
          real_T (*c9_nonlinear_params)[4];
          real_T (*c9_p_FK_total)[3];
          real_T (*c9_p_FK_l_total)[3];
          c9_p_FK_l_total = (real_T (*)[3])ssGetOutputPortSignal
            (chartInstance->S, 5);
          c9_p_FK_total = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
            4);
          c9_psi_m = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
          c9_nonlinear_params = (real_T (*)[4])ssGetInputPortSignal
            (chartInstance->S, 3);
          c9_BodyMoment = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
            2);
          c9_Disp = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 2);
          c9_BodyForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
            1);
          c9_t = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c9_STL = (real_T (*)[9846])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c9_STL);
          _SFD_SET_DATA_VALUE_PTR(1U, c9_t);
          _SFD_SET_DATA_VALUE_PTR(2U, *c9_BodyForce);
          _SFD_SET_DATA_VALUE_PTR(3U, *c9_Disp);
          _SFD_SET_DATA_VALUE_PTR(4U, *c9_BodyMoment);
          _SFD_SET_DATA_VALUE_PTR(5U, *c9_nonlinear_params);
          _SFD_SET_DATA_VALUE_PTR(6U, c9_psi_m);
          _SFD_SET_DATA_VALUE_PTR(7U, *c9_p_FK_total);
          _SFD_SET_DATA_VALUE_PTR(8U, *c9_p_FK_l_total);
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
  return "AKneyHlPQPmV8Irf0j3QQG";
}

static void sf_opaque_initialize_c9_WEC_Sim_Driver(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc9_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c9_WEC_Sim_Driver((SFc9_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar);
  initialize_c9_WEC_Sim_Driver((SFc9_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c9_WEC_Sim_Driver(void *chartInstanceVar)
{
  enable_c9_WEC_Sim_Driver((SFc9_WEC_Sim_DriverInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c9_WEC_Sim_Driver(void *chartInstanceVar)
{
  disable_c9_WEC_Sim_Driver((SFc9_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c9_WEC_Sim_Driver(void *chartInstanceVar)
{
  sf_c9_WEC_Sim_Driver((SFc9_WEC_Sim_DriverInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c9_WEC_Sim_Driver(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c9_WEC_Sim_Driver
    ((SFc9_WEC_Sim_DriverInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c9_WEC_Sim_Driver();/* state var info */
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

extern void sf_internal_set_sim_state_c9_WEC_Sim_Driver(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c9_WEC_Sim_Driver();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c9_WEC_Sim_Driver((SFc9_WEC_Sim_DriverInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c9_WEC_Sim_Driver(SimStruct* S)
{
  return sf_internal_get_sim_state_c9_WEC_Sim_Driver(S);
}

static void sf_opaque_set_sim_state_c9_WEC_Sim_Driver(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c9_WEC_Sim_Driver(S, st);
}

static void sf_opaque_terminate_c9_WEC_Sim_Driver(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc9_WEC_Sim_DriverInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_WEC_Sim_Driver_optimization_info();
    }

    finalize_c9_WEC_Sim_Driver((SFc9_WEC_Sim_DriverInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc9_WEC_Sim_Driver((SFc9_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c9_WEC_Sim_Driver(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c9_WEC_Sim_Driver((SFc9_WEC_Sim_DriverInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c9_WEC_Sim_Driver(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_WEC_Sim_Driver_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      9);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,9,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,9,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,9);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,9,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,9,5);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=5; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 4; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,9);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1027358804U));
  ssSetChecksum1(S,(667148984U));
  ssSetChecksum2(S,(1145631068U));
  ssSetChecksum3(S,(3340633505U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c9_WEC_Sim_Driver(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c9_WEC_Sim_Driver(SimStruct *S)
{
  SFc9_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc9_WEC_Sim_DriverInstanceStruct *)utMalloc(sizeof
    (SFc9_WEC_Sim_DriverInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc9_WEC_Sim_DriverInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c9_WEC_Sim_Driver;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c9_WEC_Sim_Driver;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c9_WEC_Sim_Driver;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c9_WEC_Sim_Driver;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c9_WEC_Sim_Driver;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c9_WEC_Sim_Driver;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c9_WEC_Sim_Driver;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c9_WEC_Sim_Driver;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c9_WEC_Sim_Driver;
  chartInstance->chartInfo.mdlStart = mdlStart_c9_WEC_Sim_Driver;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c9_WEC_Sim_Driver;
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

void c9_WEC_Sim_Driver_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c9_WEC_Sim_Driver(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c9_WEC_Sim_Driver(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c9_WEC_Sim_Driver(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c9_WEC_Sim_Driver_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
