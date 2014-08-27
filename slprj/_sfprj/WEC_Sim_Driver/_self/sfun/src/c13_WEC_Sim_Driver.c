/* Include files */

#include <stddef.h>
#include "blas.h"
#include "WEC_Sim_Driver_sfun.h"
#include "c13_WEC_Sim_Driver.h"
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
static const char * c13_debug_family_names[64] = { "a", "b", "c", "axisRotx",
  "axisRoty", "dX", "dZ", "angleRotx", "angleRoty", "Amp", "k", "w", "d", "psi",
  "psi_l", "psi_avg", "psi_l_avg", "STL_l", "i", "j", "q_l", "q", "costhetay",
  "sinthetay", "costhetax", "sinthetax", "x_m", "y_m", "z_m", "r_m", "r_a",
  "r_b", "r_c", "AB", "AC", "CP", "area", "x_m_l", "y_m_l", "z_m_l", "r_m_l",
  "r_a_l", "r_b_l", "r_c_l", "AB_l", "AC_l", "CP_l", "area_l", "p_HS", "p_FK",
  "p_FK_l", "p_total", "PanelMoment", "nargin", "nargout", "STL", "t", "Disp2",
  "nonlinear_params", "BodyForce", "BodyMoment", "psi_m", "p_FK_total",
  "p_FK_l_total" };

/* Function Declarations */
static void initialize_c13_WEC_Sim_Driver(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void initialize_params_c13_WEC_Sim_Driver
  (SFc13_WEC_Sim_DriverInstanceStruct *chartInstance);
static void enable_c13_WEC_Sim_Driver(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void disable_c13_WEC_Sim_Driver(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void c13_update_debugger_state_c13_WEC_Sim_Driver
  (SFc13_WEC_Sim_DriverInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c13_WEC_Sim_Driver
  (SFc13_WEC_Sim_DriverInstanceStruct *chartInstance);
static void set_sim_state_c13_WEC_Sim_Driver(SFc13_WEC_Sim_DriverInstanceStruct *
  chartInstance, const mxArray *c13_st);
static void finalize_c13_WEC_Sim_Driver(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void sf_c13_WEC_Sim_Driver(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void c13_chartstep_c13_WEC_Sim_Driver(SFc13_WEC_Sim_DriverInstanceStruct *
  chartInstance);
static void initSimStructsc13_WEC_Sim_Driver(SFc13_WEC_Sim_DriverInstanceStruct *
  chartInstance);
static void registerMessagesc13_WEC_Sim_Driver
  (SFc13_WEC_Sim_DriverInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c13_machineNumber, uint32_T
  c13_chartNumber);
static const mxArray *c13_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static void c13_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_p_FK_l_total, const char_T *c13_identifier,
  real_T c13_y[3]);
static void c13_b_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId,
  real_T c13_y[3]);
static void c13_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData);
static const mxArray *c13_b_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static real_T c13_c_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_psi_m, const char_T *c13_identifier);
static real_T c13_d_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId);
static void c13_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData);
static const mxArray *c13_c_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static const mxArray *c13_d_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static const mxArray *c13_e_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static const mxArray *c13_f_sf_marshallOut(void *chartInstanceVoid, real_T
  c13_inData_data[1], int32_T c13_inData_sizes[2]);
static void c13_e_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId,
  real_T c13_y_data[1], int32_T c13_y_sizes[2]);
static void c13_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, real_T c13_outData_data[1],
  int32_T c13_outData_sizes[2]);
static const mxArray *c13_g_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static void c13_f_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId,
  real_T c13_y[3]);
static void c13_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData);
static const mxArray *c13_h_sf_marshallOut(void *chartInstanceVoid, real_T
  c13_inData_data[3], int32_T c13_inData_sizes[2]);
static void c13_g_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId,
  real_T c13_y_data[3], int32_T c13_y_sizes[2]);
static void c13_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, real_T c13_outData_data[3],
  int32_T c13_outData_sizes[2]);
static const mxArray *c13_i_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static void c13_h_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId,
  real_T c13_y[3]);
static void c13_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData);
static void c13_i_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId,
  real_T c13_y[23742]);
static void c13_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData);
static const mxArray *c13_j_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static void c13_j_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId,
  real_T c13_y[7914]);
static void c13_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData);
static void c13_info_helper(c13_ResolvedFunctionInfo c13_info[31]);
static void c13_cross(SFc13_WEC_Sim_DriverInstanceStruct *chartInstance, real_T
                      c13_a[3], real_T c13_b[3], real_T c13_c[3]);
static void c13_cosh(SFc13_WEC_Sim_DriverInstanceStruct *chartInstance, real_T
                     c13_x_data[1], int32_T c13_x_sizes[2], real_T c13_b_x_data
                     [1], int32_T c13_b_x_sizes[2]);
static const mxArray *c13_k_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData);
static int32_T c13_k_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId);
static void c13_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData);
static uint8_T c13_l_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_b_is_active_c13_WEC_Sim_Driver, const
  char_T *c13_identifier);
static uint8_T c13_m_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId);
static void c13_b_cosh(SFc13_WEC_Sim_DriverInstanceStruct *chartInstance, real_T
  c13_x_data[1], int32_T c13_x_sizes[2]);
static void init_dsm_address_info(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c13_WEC_Sim_Driver(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
  chartInstance->c13_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c13_is_active_c13_WEC_Sim_Driver = 0U;
}

static void initialize_params_c13_WEC_Sim_Driver
  (SFc13_WEC_Sim_DriverInstanceStruct *chartInstance)
{
}

static void enable_c13_WEC_Sim_Driver(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c13_WEC_Sim_Driver(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c13_update_debugger_state_c13_WEC_Sim_Driver
  (SFc13_WEC_Sim_DriverInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c13_WEC_Sim_Driver
  (SFc13_WEC_Sim_DriverInstanceStruct *chartInstance)
{
  const mxArray *c13_st;
  const mxArray *c13_y = NULL;
  int32_T c13_i0;
  real_T c13_u[3];
  const mxArray *c13_b_y = NULL;
  int32_T c13_i1;
  real_T c13_b_u[3];
  const mxArray *c13_c_y = NULL;
  int32_T c13_i2;
  real_T c13_c_u[3];
  const mxArray *c13_d_y = NULL;
  int32_T c13_i3;
  real_T c13_d_u[3];
  const mxArray *c13_e_y = NULL;
  real_T c13_hoistedGlobal;
  real_T c13_e_u;
  const mxArray *c13_f_y = NULL;
  uint8_T c13_b_hoistedGlobal;
  uint8_T c13_f_u;
  const mxArray *c13_g_y = NULL;
  real_T *c13_psi_m;
  real_T (*c13_p_FK_total)[3];
  real_T (*c13_p_FK_l_total)[3];
  real_T (*c13_BodyMoment)[3];
  real_T (*c13_BodyForce)[3];
  c13_p_FK_l_total = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 5);
  c13_p_FK_total = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
  c13_psi_m = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c13_BodyMoment = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c13_BodyForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c13_st = NULL;
  c13_st = NULL;
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_createcellarray(6), FALSE);
  for (c13_i0 = 0; c13_i0 < 3; c13_i0++) {
    c13_u[c13_i0] = (*c13_BodyForce)[c13_i0];
  }

  c13_b_y = NULL;
  sf_mex_assign(&c13_b_y, sf_mex_create("y", c13_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_setcell(c13_y, 0, c13_b_y);
  for (c13_i1 = 0; c13_i1 < 3; c13_i1++) {
    c13_b_u[c13_i1] = (*c13_BodyMoment)[c13_i1];
  }

  c13_c_y = NULL;
  sf_mex_assign(&c13_c_y, sf_mex_create("y", c13_b_u, 0, 0U, 1U, 0U, 1, 3),
                FALSE);
  sf_mex_setcell(c13_y, 1, c13_c_y);
  for (c13_i2 = 0; c13_i2 < 3; c13_i2++) {
    c13_c_u[c13_i2] = (*c13_p_FK_l_total)[c13_i2];
  }

  c13_d_y = NULL;
  sf_mex_assign(&c13_d_y, sf_mex_create("y", c13_c_u, 0, 0U, 1U, 0U, 1, 3),
                FALSE);
  sf_mex_setcell(c13_y, 2, c13_d_y);
  for (c13_i3 = 0; c13_i3 < 3; c13_i3++) {
    c13_d_u[c13_i3] = (*c13_p_FK_total)[c13_i3];
  }

  c13_e_y = NULL;
  sf_mex_assign(&c13_e_y, sf_mex_create("y", c13_d_u, 0, 0U, 1U, 0U, 1, 3),
                FALSE);
  sf_mex_setcell(c13_y, 3, c13_e_y);
  c13_hoistedGlobal = *c13_psi_m;
  c13_e_u = c13_hoistedGlobal;
  c13_f_y = NULL;
  sf_mex_assign(&c13_f_y, sf_mex_create("y", &c13_e_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c13_y, 4, c13_f_y);
  c13_b_hoistedGlobal = chartInstance->c13_is_active_c13_WEC_Sim_Driver;
  c13_f_u = c13_b_hoistedGlobal;
  c13_g_y = NULL;
  sf_mex_assign(&c13_g_y, sf_mex_create("y", &c13_f_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c13_y, 5, c13_g_y);
  sf_mex_assign(&c13_st, c13_y, FALSE);
  return c13_st;
}

static void set_sim_state_c13_WEC_Sim_Driver(SFc13_WEC_Sim_DriverInstanceStruct *
  chartInstance, const mxArray *c13_st)
{
  const mxArray *c13_u;
  real_T c13_dv0[3];
  int32_T c13_i4;
  real_T c13_dv1[3];
  int32_T c13_i5;
  real_T c13_dv2[3];
  int32_T c13_i6;
  real_T c13_dv3[3];
  int32_T c13_i7;
  real_T *c13_psi_m;
  real_T (*c13_BodyForce)[3];
  real_T (*c13_BodyMoment)[3];
  real_T (*c13_p_FK_l_total)[3];
  real_T (*c13_p_FK_total)[3];
  c13_p_FK_l_total = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 5);
  c13_p_FK_total = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
  c13_psi_m = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c13_BodyMoment = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c13_BodyForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c13_doneDoubleBufferReInit = TRUE;
  c13_u = sf_mex_dup(c13_st);
  c13_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c13_u, 0)),
                       "BodyForce", c13_dv0);
  for (c13_i4 = 0; c13_i4 < 3; c13_i4++) {
    (*c13_BodyForce)[c13_i4] = c13_dv0[c13_i4];
  }

  c13_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c13_u, 1)),
                       "BodyMoment", c13_dv1);
  for (c13_i5 = 0; c13_i5 < 3; c13_i5++) {
    (*c13_BodyMoment)[c13_i5] = c13_dv1[c13_i5];
  }

  c13_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c13_u, 2)),
                       "p_FK_l_total", c13_dv2);
  for (c13_i6 = 0; c13_i6 < 3; c13_i6++) {
    (*c13_p_FK_l_total)[c13_i6] = c13_dv2[c13_i6];
  }

  c13_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c13_u, 3)),
                       "p_FK_total", c13_dv3);
  for (c13_i7 = 0; c13_i7 < 3; c13_i7++) {
    (*c13_p_FK_total)[c13_i7] = c13_dv3[c13_i7];
  }

  *c13_psi_m = c13_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c13_u, 4)), "psi_m");
  chartInstance->c13_is_active_c13_WEC_Sim_Driver = c13_l_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c13_u, 5)),
     "is_active_c13_WEC_Sim_Driver");
  sf_mex_destroy(&c13_u);
  c13_update_debugger_state_c13_WEC_Sim_Driver(chartInstance);
  sf_mex_destroy(&c13_st);
}

static void finalize_c13_WEC_Sim_Driver(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
}

static void sf_c13_WEC_Sim_Driver(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
  int32_T c13_i8;
  int32_T c13_i9;
  int32_T c13_i10;
  int32_T c13_i11;
  int32_T c13_i12;
  int32_T c13_i13;
  int32_T c13_i14;
  real_T *c13_t;
  real_T *c13_psi_m;
  real_T (*c13_p_FK_l_total)[3];
  real_T (*c13_p_FK_total)[3];
  real_T (*c13_nonlinear_params)[4];
  real_T (*c13_BodyMoment)[3];
  real_T (*c13_Disp2)[6];
  real_T (*c13_BodyForce)[3];
  real_T (*c13_STL)[23742];
  c13_p_FK_l_total = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 5);
  c13_p_FK_total = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
  c13_psi_m = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c13_nonlinear_params = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S, 3);
  c13_BodyMoment = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c13_Disp2 = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 2);
  c13_BodyForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c13_t = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c13_STL = (real_T (*)[23742])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 7U, chartInstance->c13_sfEvent);
  for (c13_i8 = 0; c13_i8 < 23742; c13_i8++) {
    _SFD_DATA_RANGE_CHECK((*c13_STL)[c13_i8], 0U);
  }

  _SFD_DATA_RANGE_CHECK(*c13_t, 1U);
  for (c13_i9 = 0; c13_i9 < 3; c13_i9++) {
    _SFD_DATA_RANGE_CHECK((*c13_BodyForce)[c13_i9], 2U);
  }

  for (c13_i10 = 0; c13_i10 < 6; c13_i10++) {
    _SFD_DATA_RANGE_CHECK((*c13_Disp2)[c13_i10], 3U);
  }

  for (c13_i11 = 0; c13_i11 < 3; c13_i11++) {
    _SFD_DATA_RANGE_CHECK((*c13_BodyMoment)[c13_i11], 4U);
  }

  for (c13_i12 = 0; c13_i12 < 4; c13_i12++) {
    _SFD_DATA_RANGE_CHECK((*c13_nonlinear_params)[c13_i12], 5U);
  }

  _SFD_DATA_RANGE_CHECK(*c13_psi_m, 6U);
  for (c13_i13 = 0; c13_i13 < 3; c13_i13++) {
    _SFD_DATA_RANGE_CHECK((*c13_p_FK_total)[c13_i13], 7U);
  }

  for (c13_i14 = 0; c13_i14 < 3; c13_i14++) {
    _SFD_DATA_RANGE_CHECK((*c13_p_FK_l_total)[c13_i14], 8U);
  }

  chartInstance->c13_sfEvent = CALL_EVENT;
  c13_chartstep_c13_WEC_Sim_Driver(chartInstance);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_WEC_Sim_DriverMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c13_chartstep_c13_WEC_Sim_Driver(SFc13_WEC_Sim_DriverInstanceStruct *
  chartInstance)
{
  real_T c13_hoistedGlobal;
  int32_T c13_i15;
  static real_T c13_STL[23742];
  real_T c13_t;
  int32_T c13_i16;
  real_T c13_Disp2[6];
  int32_T c13_i17;
  real_T c13_nonlinear_params[4];
  uint32_T c13_debug_family_var_map[64];
  real_T c13_a;
  real_T c13_b;
  real_T c13_c;
  real_T c13_axisRotx[3];
  real_T c13_axisRoty[3];
  real_T c13_dX;
  real_T c13_dZ;
  real_T c13_angleRotx;
  real_T c13_angleRoty;
  real_T c13_Amp;
  real_T c13_k;
  real_T c13_w;
  real_T c13_d;
  static real_T c13_psi[7914];
  real_T c13_psi_l[7914];
  real_T c13_psi_avg[7914];
  real_T c13_psi_l_avg[7914];
  static real_T c13_STL_l[23742];
  real_T c13_i;
  real_T c13_j;
  real_T c13_q_l[3];
  real_T c13_q[3];
  real_T c13_costhetay;
  real_T c13_sinthetay;
  real_T c13_costhetax;
  real_T c13_sinthetax;
  real_T c13_x_m;
  real_T c13_y_m;
  real_T c13_z_m;
  real_T c13_r_m[3];
  real_T c13_r_a[3];
  real_T c13_r_b[3];
  real_T c13_r_c[3];
  real_T c13_AB[3];
  real_T c13_AC[3];
  real_T c13_CP[3];
  real_T c13_area[3];
  real_T c13_x_m_l;
  real_T c13_y_m_l;
  real_T c13_z_m_l;
  real_T c13_r_m_l[3];
  real_T c13_r_a_l[3];
  real_T c13_r_b_l[3];
  real_T c13_r_c_l[3];
  real_T c13_AB_l[3];
  real_T c13_AC_l[3];
  real_T c13_CP_l[3];
  real_T c13_area_l[3];
  real_T c13_p_HS[3];
  int32_T c13_p_FK_sizes[2];
  real_T c13_p_FK_data[3];
  int32_T c13_p_FK_l_sizes[2];
  real_T c13_p_FK_l_data[3];
  real_T c13_p_total[3];
  real_T c13_PanelMoment[3];
  int32_T c13_psi_avg_sizes[2];
  real_T c13_psi_avg_data[1];
  int32_T c13_psi_l_avg_sizes[2];
  real_T c13_psi_l_avg_data[1];
  real_T c13_nargin = 4.0;
  real_T c13_nargout = 5.0;
  real_T c13_BodyForce[3];
  real_T c13_BodyMoment[3];
  real_T c13_psi_m;
  real_T c13_p_FK_total[3];
  real_T c13_p_FK_l_total[3];
  int32_T c13_i18;
  static real_T c13_dv4[3] = { 1.0, 0.0, 0.0 };

  int32_T c13_i19;
  static real_T c13_dv5[3] = { 0.0, 1.0, 0.0 };

  int32_T c13_i20;
  int32_T c13_i21;
  int32_T c13_i22;
  int32_T c13_i23;
  int32_T c13_i24;
  int32_T c13_b_i;
  int32_T c13_b_j;
  int32_T c13_i25;
  real_T c13_b_a;
  real_T c13_b_b;
  real_T c13_y;
  real_T c13_c_a;
  real_T c13_c_b;
  real_T c13_b_y;
  real_T c13_x;
  real_T c13_b_x;
  real_T c13_d_a;
  real_T c13_d_b;
  real_T c13_c_y;
  int32_T c13_c_j;
  int32_T c13_c_i;
  int32_T c13_i26;
  int32_T c13_d_i;
  int32_T c13_d_j;
  int32_T c13_i27;
  real_T c13_e_a;
  real_T c13_e_b;
  real_T c13_d_y;
  real_T c13_f_a;
  real_T c13_f_b;
  real_T c13_e_y;
  real_T c13_c_x;
  real_T c13_d_x;
  real_T c13_g_a;
  real_T c13_g_b;
  real_T c13_e_x;
  real_T c13_f_x;
  real_T c13_g_x;
  real_T c13_h_x;
  real_T c13_h_a;
  real_T c13_f_y;
  real_T c13_i_a;
  real_T c13_g_y;
  real_T c13_j_a;
  real_T c13_h_b;
  real_T c13_h_y;
  real_T c13_k_a;
  real_T c13_i_y;
  real_T c13_l_a;
  real_T c13_j_y;
  real_T c13_i_b;
  real_T c13_k_y;
  real_T c13_m_a;
  real_T c13_j_b;
  real_T c13_l_y;
  real_T c13_n_a;
  real_T c13_m_y;
  real_T c13_o_a;
  real_T c13_n_y;
  real_T c13_k_b;
  real_T c13_o_y;
  real_T c13_p_a;
  real_T c13_l_b;
  real_T c13_p_y;
  real_T c13_q_a;
  real_T c13_q_y;
  real_T c13_s_a;
  real_T c13_r_y;
  real_T c13_m_b;
  real_T c13_s_y;
  real_T c13_t_a;
  real_T c13_n_b;
  real_T c13_t_y;
  real_T c13_u_a;
  real_T c13_u_y;
  real_T c13_v_a;
  real_T c13_v_y;
  real_T c13_w_a;
  real_T c13_o_b;
  real_T c13_w_y;
  real_T c13_x_a;
  real_T c13_x_y;
  real_T c13_y_a;
  real_T c13_y_y;
  real_T c13_p_b;
  real_T c13_ab_y;
  real_T c13_ab_a;
  real_T c13_q_b;
  real_T c13_bb_y;
  real_T c13_bb_a;
  real_T c13_cb_y;
  real_T c13_cb_a;
  real_T c13_db_y;
  real_T c13_s_b;
  real_T c13_eb_y;
  real_T c13_db_a;
  real_T c13_t_b;
  real_T c13_fb_y;
  real_T c13_eb_a;
  real_T c13_gb_y;
  real_T c13_fb_a;
  real_T c13_hb_y;
  real_T c13_u_b;
  real_T c13_ib_y;
  real_T c13_gb_a;
  real_T c13_v_b;
  real_T c13_jb_y;
  real_T c13_hb_a;
  real_T c13_kb_y;
  real_T c13_ib_a;
  real_T c13_lb_y;
  real_T c13_jb_a;
  real_T c13_w_b;
  real_T c13_mb_y;
  int32_T c13_e_j;
  int32_T c13_e_i;
  int32_T c13_i28;
  int32_T c13_f_i;
  int32_T c13_f_j;
  int32_T c13_i29;
  real_T c13_i_x;
  real_T c13_j_x;
  real_T c13_k_x;
  real_T c13_l_x;
  real_T c13_kb_a;
  real_T c13_nb_y;
  real_T c13_lb_a;
  real_T c13_ob_y;
  real_T c13_mb_a;
  real_T c13_x_b;
  real_T c13_pb_y;
  real_T c13_nb_a;
  real_T c13_qb_y;
  real_T c13_ob_a;
  real_T c13_rb_y;
  real_T c13_y_b;
  real_T c13_sb_y;
  real_T c13_pb_a;
  real_T c13_ab_b;
  real_T c13_tb_y;
  real_T c13_qb_a;
  real_T c13_ub_y;
  real_T c13_rb_a;
  real_T c13_vb_y;
  real_T c13_bb_b;
  real_T c13_wb_y;
  real_T c13_sb_a;
  real_T c13_cb_b;
  real_T c13_xb_y;
  real_T c13_tb_a;
  real_T c13_yb_y;
  real_T c13_ub_a;
  real_T c13_ac_y;
  real_T c13_db_b;
  real_T c13_bc_y;
  real_T c13_vb_a;
  real_T c13_eb_b;
  real_T c13_cc_y;
  real_T c13_wb_a;
  real_T c13_dc_y;
  real_T c13_xb_a;
  real_T c13_ec_y;
  real_T c13_yb_a;
  real_T c13_fb_b;
  real_T c13_fc_y;
  real_T c13_ac_a;
  real_T c13_gc_y;
  real_T c13_bc_a;
  real_T c13_hc_y;
  real_T c13_gb_b;
  real_T c13_ic_y;
  real_T c13_cc_a;
  real_T c13_hb_b;
  real_T c13_jc_y;
  real_T c13_dc_a;
  real_T c13_kc_y;
  real_T c13_ec_a;
  real_T c13_lc_y;
  real_T c13_ib_b;
  real_T c13_mc_y;
  real_T c13_fc_a;
  real_T c13_jb_b;
  real_T c13_nc_y;
  real_T c13_gc_a;
  real_T c13_oc_y;
  real_T c13_hc_a;
  real_T c13_pc_y;
  real_T c13_kb_b;
  real_T c13_qc_y;
  real_T c13_ic_a;
  real_T c13_lb_b;
  real_T c13_rc_y;
  real_T c13_jc_a;
  real_T c13_sc_y;
  real_T c13_kc_a;
  real_T c13_tc_y;
  real_T c13_lc_a;
  real_T c13_mb_b;
  real_T c13_uc_y;
  real_T c13_mc_a;
  real_T c13_nb_b;
  real_T c13_vc_y;
  real_T c13_nc_a;
  real_T c13_ob_b;
  real_T c13_wc_y;
  real_T c13_m_x;
  real_T c13_n_x;
  real_T c13_oc_a;
  real_T c13_pb_b;
  real_T c13_xc_y;
  int32_T c13_g_j;
  int32_T c13_g_i;
  int32_T c13_i30;
  int32_T c13_i31;
  int32_T c13_i32;
  int32_T c13_i33;
  int32_T c13_i34;
  int32_T c13_h_i;
  real_T c13_A;
  real_T c13_o_x;
  real_T c13_p_x;
  real_T c13_b_A;
  real_T c13_q_x;
  real_T c13_r_x;
  real_T c13_c_A;
  real_T c13_s_x;
  real_T c13_t_x;
  int32_T c13_i35;
  int32_T c13_i36;
  int32_T c13_i37;
  real_T c13_b_AC[3];
  int32_T c13_i38;
  real_T c13_b_AB[3];
  real_T c13_dv6[3];
  int32_T c13_i39;
  int32_T c13_i40;
  real_T c13_qb_b[3];
  int32_T c13_i41;
  real_T c13_d_A;
  real_T c13_u_x;
  real_T c13_v_x;
  real_T c13_e_A;
  real_T c13_w_x;
  real_T c13_x_x;
  real_T c13_f_A;
  real_T c13_y_x;
  real_T c13_ab_x;
  int32_T c13_i42;
  int32_T c13_i43;
  int32_T c13_i44;
  real_T c13_b_AC_l[3];
  int32_T c13_i45;
  real_T c13_b_AB_l[3];
  real_T c13_dv7[3];
  int32_T c13_i46;
  int32_T c13_i47;
  int32_T c13_i48;
  real_T c13_g_A;
  real_T c13_bb_x;
  real_T c13_cb_x;
  real_T c13_yc_y;
  int32_T c13_b_psi_avg;
  int32_T c13_c_psi_avg;
  real_T c13_h_A;
  real_T c13_db_x;
  real_T c13_eb_x;
  real_T c13_ad_y;
  int32_T c13_b_psi_l_avg;
  int32_T c13_c_psi_l_avg;
  real_T c13_pc_a;
  int32_T c13_i49;
  int32_T c13_i50;
  int32_T c13_i51;
  int32_T c13_b_sizes[2];
  int32_T c13_rb_b;
  int32_T c13_sb_b;
  int32_T c13_loop_ub;
  int32_T c13_i52;
  real_T c13_b_data[1];
  int32_T c13_y_sizes[2];
  int32_T c13_i53;
  real_T c13_y_data[3];
  real_T c13_qc_a;
  int32_T c13_tb_b;
  int32_T c13_ub_b;
  int32_T c13_b_loop_ub;
  int32_T c13_i54;
  int32_T c13_vb_b;
  int32_T c13_wb_b;
  int32_T c13_xb_b;
  int32_T c13_yb_b;
  int32_T c13_c_loop_ub;
  int32_T c13_i55;
  int32_T c13_b_y_sizes[2];
  int32_T c13_i56;
  real_T c13_b_y_data[3];
  real_T c13_rc_a;
  real_T c13_ac_b;
  real_T c13_bd_y;
  real_T c13_fb_x;
  real_T c13_gb_x;
  real_T c13_B;
  real_T c13_cd_y;
  real_T c13_dd_y;
  int32_T c13_p_FK;
  int32_T c13_b_p_FK;
  int32_T c13_d_loop_ub;
  int32_T c13_i57;
  int32_T c13_i58;
  int32_T c13_bc_b;
  int32_T c13_cc_b;
  int32_T c13_e_loop_ub;
  int32_T c13_i59;
  int32_T c13_i60;
  real_T c13_sc_a;
  int32_T c13_dc_b;
  int32_T c13_ec_b;
  int32_T c13_f_loop_ub;
  int32_T c13_i61;
  int32_T c13_fc_b;
  int32_T c13_gc_b;
  int32_T c13_hc_b;
  int32_T c13_ic_b;
  int32_T c13_g_loop_ub;
  int32_T c13_i62;
  int32_T c13_i63;
  real_T c13_tc_a;
  real_T c13_jc_b;
  real_T c13_ed_y;
  real_T c13_hb_x;
  real_T c13_ib_x;
  real_T c13_b_B;
  real_T c13_fd_y;
  real_T c13_gd_y;
  int32_T c13_p_FK_l;
  int32_T c13_b_p_FK_l;
  int32_T c13_h_loop_ub;
  int32_T c13_i64;
  int32_T c13_i65;
  int32_T c13_i66;
  int32_T c13_i67;
  real_T c13_b_r_m[3];
  int32_T c13_i68;
  real_T c13_b_p_total[3];
  real_T c13_dv8[3];
  int32_T c13_i69;
  int32_T c13_i70;
  int32_T c13_i71;
  int32_T c13_i72;
  int32_T c13_i73;
  int32_T c13_i74;
  int32_T c13_i75;
  int32_T c13_i76;
  real_T *c13_b_psi_m;
  real_T *c13_b_t;
  real_T (*c13_b_BodyForce)[3];
  real_T (*c13_b_BodyMoment)[3];
  real_T (*c13_b_p_FK_total)[3];
  real_T (*c13_b_p_FK_l_total)[3];
  real_T (*c13_b_nonlinear_params)[4];
  real_T (*c13_b_Disp2)[6];
  real_T (*c13_b_STL)[23742];
  c13_b_p_FK_l_total = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 5);
  c13_b_p_FK_total = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 4);
  c13_b_psi_m = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c13_b_nonlinear_params = (real_T (*)[4])ssGetInputPortSignal(chartInstance->S,
    3);
  c13_b_BodyMoment = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 2);
  c13_b_Disp2 = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 2);
  c13_b_BodyForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S, 1);
  c13_b_t = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c13_b_STL = (real_T (*)[23742])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 7U, chartInstance->c13_sfEvent);
  c13_hoistedGlobal = *c13_b_t;
  for (c13_i15 = 0; c13_i15 < 23742; c13_i15++) {
    c13_STL[c13_i15] = (*c13_b_STL)[c13_i15];
  }

  c13_t = c13_hoistedGlobal;
  for (c13_i16 = 0; c13_i16 < 6; c13_i16++) {
    c13_Disp2[c13_i16] = (*c13_b_Disp2)[c13_i16];
  }

  for (c13_i17 = 0; c13_i17 < 4; c13_i17++) {
    c13_nonlinear_params[c13_i17] = (*c13_b_nonlinear_params)[c13_i17];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 64U, 66U, c13_debug_family_names,
    c13_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c13_a, 0U, c13_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c13_b, 1U, c13_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_c, 2U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c13_axisRotx, 3U, c13_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c13_axisRoty, 4U, c13_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_dX, 5U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_dZ, 6U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_angleRotx, 7U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_angleRoty, 8U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_Amp, 9U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_k, 10U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_w, 11U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_d, 12U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_psi, 13U, c13_j_sf_marshallOut,
    c13_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_psi_l, 14U, c13_j_sf_marshallOut,
    c13_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_psi_avg, MAX_uint32_T,
    c13_j_sf_marshallOut, c13_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_psi_l_avg, MAX_uint32_T,
    c13_j_sf_marshallOut, c13_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_STL_l, 17U, c13_e_sf_marshallOut,
    c13_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_i, 18U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_j, 19U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_q_l, 20U, c13_i_sf_marshallOut,
    c13_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_q, 21U, c13_i_sf_marshallOut,
    c13_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_costhetay, 22U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_sinthetay, 23U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_costhetax, 24U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_sinthetax, 25U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_x_m, 26U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_y_m, 27U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_z_m, 28U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_r_m, 29U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_r_a, 30U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_r_b, 31U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_r_c, 32U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_AB, 33U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_AC, 34U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_CP, 35U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_area, 36U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_x_m_l, 37U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_y_m_l, 38U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_z_m_l, 39U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_r_m_l, 40U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_r_a_l, 41U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_r_b_l, 42U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_r_c_l, 43U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_AB_l, 44U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_AC_l, 45U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_CP_l, 46U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_area_l, 47U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_p_HS, 48U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c13_p_FK_data, (const int32_T *)
    &c13_p_FK_sizes, NULL, 0, 49, (void *)c13_h_sf_marshallOut, (void *)
    c13_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c13_p_FK_l_data, (const int32_T *)
    &c13_p_FK_l_sizes, NULL, 0, 50, (void *)c13_h_sf_marshallOut, (void *)
    c13_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_p_total, 51U, c13_g_sf_marshallOut,
    c13_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_PanelMoment, 52U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c13_psi_avg_data, (const int32_T *)
    &c13_psi_avg_sizes, NULL, 0, -1, (void *)c13_f_sf_marshallOut, (void *)
    c13_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c13_psi_l_avg_data, (const int32_T *)
    &c13_psi_l_avg_sizes, NULL, 0, -1, (void *)c13_f_sf_marshallOut, (void *)
    c13_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_nargin, 53U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_nargout, 54U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c13_STL, 55U, c13_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c13_t, 56U, c13_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c13_Disp2, 57U, c13_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c13_nonlinear_params, 58U, c13_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_BodyForce, 59U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_BodyMoment, 60U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c13_psi_m, 61U, c13_b_sf_marshallOut,
    c13_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_p_FK_total, 62U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c13_p_FK_l_total, 63U, c13_sf_marshallOut,
    c13_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 15);
  c13_a = 2638.0;
  c13_b = 3.0;
  c13_c = 3.0;
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 20);
  for (c13_i18 = 0; c13_i18 < 3; c13_i18++) {
    c13_axisRotx[c13_i18] = c13_dv4[c13_i18];
  }

  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 21);
  for (c13_i19 = 0; c13_i19 < 3; c13_i19++) {
    c13_axisRoty[c13_i19] = c13_dv5[c13_i19];
  }

  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 22);
  c13_dX = c13_Disp2[0];
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 23);
  c13_dZ = c13_Disp2[2];
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 24);
  c13_angleRotx = c13_Disp2[3];
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 25);
  c13_angleRoty = c13_Disp2[4];
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 26);
  c13_Amp = c13_nonlinear_params[0];
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 27);
  c13_k = c13_nonlinear_params[1];
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 28);
  c13_w = c13_nonlinear_params[2];
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 29);
  c13_d = c13_nonlinear_params[3];
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 30);
  for (c13_i20 = 0; c13_i20 < 7914; c13_i20++) {
    c13_psi[c13_i20] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 31);
  for (c13_i21 = 0; c13_i21 < 7914; c13_i21++) {
    c13_psi_l[c13_i21] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 32);
  c13_psi_m = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 33);
  for (c13_i22 = 0; c13_i22 < 7914; c13_i22++) {
    c13_psi_avg[c13_i22] = 0.0;
  }

  _SFD_SYMBOL_SWITCH(15U, 15U);
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 34);
  for (c13_i23 = 0; c13_i23 < 7914; c13_i23++) {
    c13_psi_l_avg[c13_i23] = 0.0;
  }

  _SFD_SYMBOL_SWITCH(16U, 16U);
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 35);
  for (c13_i24 = 0; c13_i24 < 23742; c13_i24++) {
    c13_STL_l[c13_i24] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 38);
  c13_i = 1.0;
  c13_b_i = 0;
  while (c13_b_i < 2638) {
    c13_i = 1.0 + (real_T)c13_b_i;
    CV_EML_FOR(0, 1, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 39);
    c13_j = 1.0;
    c13_b_j = 0;
    while (c13_b_j < 3) {
      c13_j = 1.0 + (real_T)c13_b_j;
      CV_EML_FOR(0, 1, 1, 1);
      _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 40);
      for (c13_i25 = 0; c13_i25 < 3; c13_i25++) {
        c13_q_l[c13_i25] = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 42);
      c13_q_l[0] = c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) - 1];
      _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 43);
      c13_q_l[1] = c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) + 7913];
      _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 44);
      c13_q_l[2] = c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) +
        15827] - 17.606;
      _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 45);
      if (CV_EML_IF(0, 1, 0, c13_q_l[2] > 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 46);
        c13_q_l[2] = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 48);
      c13_b_a = c13_k;
      c13_b_b = c13_q_l[0] + c13_dX;
      c13_y = c13_b_a * c13_b_b;
      c13_c_a = c13_w;
      c13_c_b = c13_t;
      c13_b_y = c13_c_a * c13_c_b;
      c13_x = c13_y - c13_b_y;
      c13_b_x = c13_x;
      c13_b_x = muDoubleScalarCos(c13_b_x);
      c13_d_a = c13_Amp;
      c13_d_b = c13_b_x;
      c13_c_y = c13_d_a * c13_d_b;
      c13_psi_l[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) - 1] = c13_c_y;
      _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 50);
      c13_c_j = (int32_T)c13_j - 1;
      c13_c_i = (int32_T)c13_i - 1;
      for (c13_i26 = 0; c13_i26 < 3; c13_i26++) {
        c13_STL_l[(c13_c_i + 2638 * c13_c_j) + 7914 * c13_i26] = c13_q_l[c13_i26];
      }

      c13_b_j++;
      _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 1, 0);
    c13_b_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 0, 0);
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 55);
  c13_i = 1.0;
  c13_d_i = 0;
  while (c13_d_i < 2638) {
    c13_i = 1.0 + (real_T)c13_d_i;
    CV_EML_FOR(0, 1, 2, 1);
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 56);
    c13_j = 1.0;
    c13_d_j = 0;
    while (c13_d_j < 3) {
      c13_j = 1.0 + (real_T)c13_d_j;
      CV_EML_FOR(0, 1, 3, 1);
      _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 57);
      for (c13_i27 = 0; c13_i27 < 3; c13_i27++) {
        c13_q[c13_i27] = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 60);
      if (CV_EML_IF(0, 1, 1, c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j -
             1)) - 1] < 0.001)) {
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 61);
        c13_e_a = c13_k;
        c13_e_b = c13_dX;
        c13_d_y = c13_e_a * c13_e_b;
        c13_f_a = c13_w;
        c13_f_b = c13_t;
        c13_e_y = c13_f_a * c13_f_b;
        c13_c_x = c13_d_y - c13_e_y;
        c13_d_x = c13_c_x;
        c13_d_x = muDoubleScalarCos(c13_d_x);
        c13_g_a = c13_Amp;
        c13_g_b = c13_d_x;
        c13_psi_m = c13_g_a * c13_g_b;
      }

      _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 65);
      if (CV_EML_IF(0, 1, 2, c13_angleRoty != 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 67);
        c13_e_x = c13_angleRoty;
        c13_costhetay = c13_e_x;
        c13_f_x = c13_costhetay;
        c13_costhetay = c13_f_x;
        c13_costhetay = muDoubleScalarCos(c13_costhetay);
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 68);
        c13_g_x = c13_angleRoty;
        c13_sinthetay = c13_g_x;
        c13_h_x = c13_sinthetay;
        c13_sinthetay = c13_h_x;
        c13_sinthetay = muDoubleScalarSin(c13_sinthetay);
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 70);
        c13_h_a = 1.0 - c13_costhetay;
        c13_f_y = c13_h_a * 0.0;
        c13_i_a = c13_f_y;
        c13_g_y = c13_i_a * 0.0;
        c13_j_a = c13_costhetay + c13_g_y;
        c13_h_b = c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) - 1];
        c13_h_y = c13_j_a * c13_h_b;
        c13_q[0] = c13_h_y;
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 71);
        c13_k_a = 1.0 - c13_costhetay;
        c13_i_y = c13_k_a * 0.0;
        c13_l_a = c13_i_y;
        c13_j_y = c13_l_a;
        c13_i_b = c13_sinthetay;
        c13_k_y = 0.0 * c13_i_b;
        c13_m_a = c13_j_y - c13_k_y;
        c13_j_b = c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) + 7913];
        c13_l_y = c13_m_a * c13_j_b;
        c13_q[0] += c13_l_y;
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 72);
        c13_n_a = 1.0 - c13_costhetay;
        c13_m_y = c13_n_a * 0.0;
        c13_o_a = c13_m_y;
        c13_n_y = c13_o_a * 0.0;
        c13_k_b = c13_sinthetay;
        c13_o_y = c13_k_b;
        c13_p_a = c13_n_y + c13_o_y;
        c13_l_b = c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) + 15827];
        c13_p_y = c13_p_a * c13_l_b;
        c13_q[0] += c13_p_y;
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 74);
        c13_q_a = 1.0 - c13_costhetay;
        c13_q_y = c13_q_a * 0.0;
        c13_s_a = c13_q_y;
        c13_r_y = c13_s_a;
        c13_m_b = c13_sinthetay;
        c13_s_y = 0.0 * c13_m_b;
        c13_t_a = c13_r_y + c13_s_y;
        c13_n_b = c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) - 1];
        c13_t_y = c13_t_a * c13_n_b;
        c13_q[1] = c13_t_y;
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 75);
        c13_u_a = 1.0 - c13_costhetay;
        c13_u_y = c13_u_a;
        c13_v_a = c13_u_y;
        c13_v_y = c13_v_a;
        c13_w_a = c13_costhetay + c13_v_y;
        c13_o_b = c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) + 7913];
        c13_w_y = c13_w_a * c13_o_b;
        c13_q[1] += c13_w_y;
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 76);
        c13_x_a = 1.0 - c13_costhetay;
        c13_x_y = c13_x_a;
        c13_y_a = c13_x_y;
        c13_y_y = c13_y_a * 0.0;
        c13_p_b = c13_sinthetay;
        c13_ab_y = 0.0 * c13_p_b;
        c13_ab_a = c13_y_y - c13_ab_y;
        c13_q_b = c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) + 15827];
        c13_bb_y = c13_ab_a * c13_q_b;
        c13_q[1] += c13_bb_y;
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 78);
        c13_bb_a = 1.0 - c13_costhetay;
        c13_cb_y = c13_bb_a * 0.0;
        c13_cb_a = c13_cb_y;
        c13_db_y = c13_cb_a * 0.0;
        c13_s_b = c13_sinthetay;
        c13_eb_y = c13_s_b;
        c13_db_a = c13_db_y - c13_eb_y;
        c13_t_b = c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) - 1];
        c13_fb_y = c13_db_a * c13_t_b;
        c13_q[2] = c13_fb_y;
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 79);
        c13_eb_a = 1.0 - c13_costhetay;
        c13_gb_y = c13_eb_a;
        c13_fb_a = c13_gb_y;
        c13_hb_y = c13_fb_a * 0.0;
        c13_u_b = c13_sinthetay;
        c13_ib_y = 0.0 * c13_u_b;
        c13_gb_a = c13_hb_y + c13_ib_y;
        c13_v_b = c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) + 7913];
        c13_jb_y = c13_gb_a * c13_v_b;
        c13_q[2] += c13_jb_y;
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 80);
        c13_hb_a = 1.0 - c13_costhetay;
        c13_kb_y = c13_hb_a * 0.0;
        c13_ib_a = c13_kb_y;
        c13_lb_y = c13_ib_a * 0.0;
        c13_jb_a = c13_costhetay + c13_lb_y;
        c13_w_b = c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) + 15827];
        c13_mb_y = c13_jb_a * c13_w_b;
        c13_q[2] += c13_mb_y;
      }

      _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 84);
      if (CV_EML_IF(0, 1, 3, c13_angleRoty != 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 86);
        c13_e_j = (int32_T)c13_j - 1;
        c13_e_i = (int32_T)c13_i - 1;
        for (c13_i28 = 0; c13_i28 < 3; c13_i28++) {
          c13_STL[(c13_e_i + 2638 * c13_e_j) + 7914 * c13_i28] = c13_q[c13_i28];
        }
      }

      c13_d_j++;
      _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 3, 0);
    c13_d_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 2, 0);
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 91);
  c13_i = 1.0;
  c13_f_i = 0;
  while (c13_f_i < 2638) {
    c13_i = 1.0 + (real_T)c13_f_i;
    CV_EML_FOR(0, 1, 4, 1);
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 92);
    c13_j = 1.0;
    c13_f_j = 0;
    while (c13_f_j < 3) {
      c13_j = 1.0 + (real_T)c13_f_j;
      CV_EML_FOR(0, 1, 5, 1);
      _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 93);
      for (c13_i29 = 0; c13_i29 < 3; c13_i29++) {
        c13_q[c13_i29] = 0.0;
      }

      _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 95);
      if (CV_EML_IF(0, 1, 4, c13_angleRotx != 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 97);
        c13_i_x = c13_angleRotx;
        c13_costhetax = c13_i_x;
        c13_j_x = c13_costhetax;
        c13_costhetax = c13_j_x;
        c13_costhetax = muDoubleScalarCos(c13_costhetax);
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 98);
        c13_k_x = c13_angleRotx;
        c13_sinthetax = c13_k_x;
        c13_l_x = c13_sinthetax;
        c13_sinthetax = c13_l_x;
        c13_sinthetax = muDoubleScalarSin(c13_sinthetax);
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 100);
        c13_kb_a = 1.0 - c13_costhetax;
        c13_nb_y = c13_kb_a;
        c13_lb_a = c13_nb_y;
        c13_ob_y = c13_lb_a;
        c13_mb_a = c13_costhetax + c13_ob_y;
        c13_x_b = c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) - 1];
        c13_pb_y = c13_mb_a * c13_x_b;
        c13_q[0] = c13_pb_y;
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 101);
        c13_nb_a = 1.0 - c13_costhetax;
        c13_qb_y = c13_nb_a;
        c13_ob_a = c13_qb_y;
        c13_rb_y = c13_ob_a * 0.0;
        c13_y_b = c13_sinthetax;
        c13_sb_y = 0.0 * c13_y_b;
        c13_pb_a = c13_rb_y - c13_sb_y;
        c13_ab_b = c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) + 7913];
        c13_tb_y = c13_pb_a * c13_ab_b;
        c13_q[0] += c13_tb_y;
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 102);
        c13_qb_a = 1.0 - c13_costhetax;
        c13_ub_y = c13_qb_a;
        c13_rb_a = c13_ub_y;
        c13_vb_y = c13_rb_a * 0.0;
        c13_bb_b = c13_sinthetax;
        c13_wb_y = 0.0 * c13_bb_b;
        c13_sb_a = c13_vb_y + c13_wb_y;
        c13_cb_b = c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) +
          15827];
        c13_xb_y = c13_sb_a * c13_cb_b;
        c13_q[0] += c13_xb_y;
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 104);
        c13_tb_a = 1.0 - c13_costhetax;
        c13_yb_y = c13_tb_a;
        c13_ub_a = c13_yb_y;
        c13_ac_y = c13_ub_a * 0.0;
        c13_db_b = c13_sinthetax;
        c13_bc_y = 0.0 * c13_db_b;
        c13_vb_a = c13_ac_y + c13_bc_y;
        c13_eb_b = c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) - 1];
        c13_cc_y = c13_vb_a * c13_eb_b;
        c13_q[1] = c13_cc_y;
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 105);
        c13_wb_a = 1.0 - c13_costhetax;
        c13_dc_y = c13_wb_a * 0.0;
        c13_xb_a = c13_dc_y;
        c13_ec_y = c13_xb_a * 0.0;
        c13_yb_a = c13_costhetax + c13_ec_y;
        c13_fb_b = c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) + 7913];
        c13_fc_y = c13_yb_a * c13_fb_b;
        c13_q[1] += c13_fc_y;
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 106);
        c13_ac_a = 1.0 - c13_costhetax;
        c13_gc_y = c13_ac_a * 0.0;
        c13_bc_a = c13_gc_y;
        c13_hc_y = c13_bc_a * 0.0;
        c13_gb_b = c13_sinthetax;
        c13_ic_y = c13_gb_b;
        c13_cc_a = c13_hc_y - c13_ic_y;
        c13_hb_b = c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) +
          15827];
        c13_jc_y = c13_cc_a * c13_hb_b;
        c13_q[1] += c13_jc_y;
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 108);
        c13_dc_a = 1.0 - c13_costhetax;
        c13_kc_y = c13_dc_a;
        c13_ec_a = c13_kc_y;
        c13_lc_y = c13_ec_a * 0.0;
        c13_ib_b = c13_sinthetax;
        c13_mc_y = 0.0 * c13_ib_b;
        c13_fc_a = c13_lc_y - c13_mc_y;
        c13_jb_b = c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) - 1];
        c13_nc_y = c13_fc_a * c13_jb_b;
        c13_q[2] = c13_nc_y;
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 109);
        c13_gc_a = 1.0 - c13_costhetax;
        c13_oc_y = c13_gc_a * 0.0;
        c13_hc_a = c13_oc_y;
        c13_pc_y = c13_hc_a * 0.0;
        c13_kb_b = c13_sinthetax;
        c13_qc_y = c13_kb_b;
        c13_ic_a = c13_pc_y + c13_qc_y;
        c13_lb_b = c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) + 7913];
        c13_rc_y = c13_ic_a * c13_lb_b;
        c13_q[2] += c13_rc_y;
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 110);
        c13_jc_a = 1.0 - c13_costhetax;
        c13_sc_y = c13_jc_a * 0.0;
        c13_kc_a = c13_sc_y;
        c13_tc_y = c13_kc_a * 0.0;
        c13_lc_a = c13_costhetax + c13_tc_y;
        c13_mb_b = c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) +
          15827];
        c13_uc_y = c13_lc_a * c13_mb_b;
        c13_q[2] += c13_uc_y;
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 112);
        c13_q[2] += c13_dZ;
      } else {
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 115);
        c13_q[0] = c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) - 1];
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 116);
        c13_q[1] = c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) + 7913];
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 117);
        c13_q[2] = c13_STL[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) +
          15827] + c13_dZ;
      }

      _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 121);
      c13_mc_a = c13_k;
      c13_nb_b = c13_q[0] + c13_dX;
      c13_vc_y = c13_mc_a * c13_nb_b;
      c13_nc_a = c13_w;
      c13_ob_b = c13_t;
      c13_wc_y = c13_nc_a * c13_ob_b;
      c13_m_x = c13_vc_y - c13_wc_y;
      c13_n_x = c13_m_x;
      c13_n_x = muDoubleScalarCos(c13_n_x);
      c13_oc_a = c13_Amp;
      c13_pb_b = c13_n_x;
      c13_xc_y = c13_oc_a * c13_pb_b;
      c13_psi[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) - 1] = c13_xc_y;
      _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 122);
      if (CV_EML_IF(0, 1, 5, c13_q[2] > c13_psi[((int32_T)c13_i + 2638 *
            ((int32_T)c13_j - 1)) - 1])) {
        _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 123);
        c13_q[2] = c13_psi[((int32_T)c13_i + 2638 * ((int32_T)c13_j - 1)) - 1];
      }

      _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 132U);
      c13_g_j = (int32_T)c13_j - 1;
      c13_g_i = (int32_T)c13_i - 1;
      for (c13_i30 = 0; c13_i30 < 3; c13_i30++) {
        c13_STL[(c13_g_i + 2638 * c13_g_j) + 7914 * c13_i30] = c13_q[c13_i30];
      }

      c13_f_j++;
      _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
    }

    CV_EML_FOR(0, 1, 5, 0);
    c13_f_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 4, 0);
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 137U);
  for (c13_i31 = 0; c13_i31 < 3; c13_i31++) {
    c13_BodyForce[c13_i31] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 138U);
  for (c13_i32 = 0; c13_i32 < 3; c13_i32++) {
    c13_BodyMoment[c13_i32] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 139U);
  for (c13_i33 = 0; c13_i33 < 3; c13_i33++) {
    c13_p_FK_total[c13_i33] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 140U);
  for (c13_i34 = 0; c13_i34 < 3; c13_i34++) {
    c13_p_FK_l_total[c13_i34] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 141U);
  c13_i = 1.0;
  c13_h_i = 0;
  while (c13_h_i < 2638) {
    c13_i = 1.0 + (real_T)c13_h_i;
    CV_EML_FOR(0, 1, 6, 1);
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 142U);
    c13_A = (c13_STL[(int32_T)c13_i - 1] + c13_STL[(int32_T)c13_i + 2637]) +
      c13_STL[(int32_T)c13_i + 5275];
    c13_o_x = c13_A;
    c13_p_x = c13_o_x;
    c13_x_m = c13_p_x / 3.0;
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 143U);
    c13_b_A = (c13_STL[(int32_T)c13_i + 7913] + c13_STL[(int32_T)c13_i + 10551])
      + c13_STL[(int32_T)c13_i + 13189];
    c13_q_x = c13_b_A;
    c13_r_x = c13_q_x;
    c13_y_m = c13_r_x / 3.0;
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 144U);
    c13_c_A = (c13_STL[(int32_T)c13_i + 15827] + c13_STL[(int32_T)c13_i + 18465])
      + c13_STL[(int32_T)c13_i + 21103];
    c13_s_x = c13_c_A;
    c13_t_x = c13_s_x;
    c13_z_m = c13_t_x / 3.0;
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 145U);
    c13_r_m[0] = c13_x_m;
    c13_r_m[1] = c13_y_m;
    c13_r_m[2] = c13_z_m;
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 147U);
    c13_r_a[0] = c13_STL[(int32_T)c13_i - 1];
    c13_r_a[1] = c13_STL[(int32_T)c13_i + 7913];
    c13_r_a[2] = c13_STL[(int32_T)c13_i + 15827];
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 148U);
    c13_r_b[0] = c13_STL[(int32_T)c13_i + 2637];
    c13_r_b[1] = c13_STL[(int32_T)c13_i + 10551];
    c13_r_b[2] = c13_STL[(int32_T)c13_i + 18465];
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 149U);
    c13_r_c[0] = c13_STL[(int32_T)c13_i + 5275];
    c13_r_c[1] = c13_STL[(int32_T)c13_i + 13189];
    c13_r_c[2] = c13_STL[(int32_T)c13_i + 21103];
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 151U);
    for (c13_i35 = 0; c13_i35 < 3; c13_i35++) {
      c13_AB[c13_i35] = c13_r_b[c13_i35] - c13_r_a[c13_i35];
    }

    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 152U);
    for (c13_i36 = 0; c13_i36 < 3; c13_i36++) {
      c13_AC[c13_i36] = c13_r_c[c13_i36] - c13_r_a[c13_i36];
    }

    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 153U);
    for (c13_i37 = 0; c13_i37 < 3; c13_i37++) {
      c13_b_AC[c13_i37] = c13_AC[c13_i37];
    }

    for (c13_i38 = 0; c13_i38 < 3; c13_i38++) {
      c13_b_AB[c13_i38] = c13_AB[c13_i38];
    }

    c13_cross(chartInstance, c13_b_AC, c13_b_AB, c13_dv6);
    for (c13_i39 = 0; c13_i39 < 3; c13_i39++) {
      c13_CP[c13_i39] = c13_dv6[c13_i39];
    }

    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 154U);
    for (c13_i40 = 0; c13_i40 < 3; c13_i40++) {
      c13_qb_b[c13_i40] = c13_CP[c13_i40];
    }

    for (c13_i41 = 0; c13_i41 < 3; c13_i41++) {
      c13_area[c13_i41] = 0.5 * c13_qb_b[c13_i41];
    }

    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 156U);
    c13_d_A = (c13_STL_l[(int32_T)c13_i - 1] + c13_STL_l[(int32_T)c13_i + 2637])
      + c13_STL_l[(int32_T)c13_i + 5275];
    c13_u_x = c13_d_A;
    c13_v_x = c13_u_x;
    c13_x_m_l = c13_v_x / 3.0;
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 157U);
    c13_e_A = (c13_STL_l[(int32_T)c13_i + 7913] + c13_STL_l[(int32_T)c13_i +
               10551]) + c13_STL_l[(int32_T)c13_i + 13189];
    c13_w_x = c13_e_A;
    c13_x_x = c13_w_x;
    c13_y_m_l = c13_x_x / 3.0;
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 158U);
    c13_f_A = (c13_STL_l[(int32_T)c13_i + 15827] + c13_STL_l[(int32_T)c13_i +
               18465]) + c13_STL_l[(int32_T)c13_i + 21103];
    c13_y_x = c13_f_A;
    c13_ab_x = c13_y_x;
    c13_z_m_l = c13_ab_x / 3.0;
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 159U);
    c13_r_m_l[0] = c13_x_m_l;
    c13_r_m_l[1] = c13_y_m_l;
    c13_r_m_l[2] = c13_z_m_l;
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 161U);
    c13_r_a_l[0] = c13_STL_l[(int32_T)c13_i - 1];
    c13_r_a_l[1] = c13_STL_l[(int32_T)c13_i + 7913];
    c13_r_a_l[2] = c13_STL_l[(int32_T)c13_i + 15827];
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 162U);
    c13_r_b_l[0] = c13_STL_l[(int32_T)c13_i + 2637];
    c13_r_b_l[1] = c13_STL_l[(int32_T)c13_i + 10551];
    c13_r_b_l[2] = c13_STL_l[(int32_T)c13_i + 18465];
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 163U);
    c13_r_c_l[0] = c13_STL_l[(int32_T)c13_i + 5275];
    c13_r_c_l[1] = c13_STL_l[(int32_T)c13_i + 13189];
    c13_r_c_l[2] = c13_STL_l[(int32_T)c13_i + 21103];
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 165U);
    for (c13_i42 = 0; c13_i42 < 3; c13_i42++) {
      c13_AB_l[c13_i42] = c13_r_b_l[c13_i42] - c13_r_a_l[c13_i42];
    }

    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 166U);
    for (c13_i43 = 0; c13_i43 < 3; c13_i43++) {
      c13_AC_l[c13_i43] = c13_r_c_l[c13_i43] - c13_r_a_l[c13_i43];
    }

    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 167U);
    for (c13_i44 = 0; c13_i44 < 3; c13_i44++) {
      c13_b_AC_l[c13_i44] = c13_AC_l[c13_i44];
    }

    for (c13_i45 = 0; c13_i45 < 3; c13_i45++) {
      c13_b_AB_l[c13_i45] = c13_AB_l[c13_i45];
    }

    c13_cross(chartInstance, c13_b_AC_l, c13_b_AB_l, c13_dv7);
    for (c13_i46 = 0; c13_i46 < 3; c13_i46++) {
      c13_CP_l[c13_i46] = c13_dv7[c13_i46];
    }

    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 168U);
    for (c13_i47 = 0; c13_i47 < 3; c13_i47++) {
      c13_qb_b[c13_i47] = c13_CP_l[c13_i47];
    }

    for (c13_i48 = 0; c13_i48 < 3; c13_i48++) {
      c13_area_l[c13_i48] = 0.5 * c13_qb_b[c13_i48];
    }

    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 170U);
    c13_g_A = (c13_psi[(int32_T)c13_i - 1] + c13_psi[(int32_T)c13_i + 2637]) +
      c13_psi[(int32_T)c13_i + 5275];
    c13_bb_x = c13_g_A;
    c13_cb_x = c13_bb_x;
    c13_yc_y = c13_cb_x / 3.0;
    c13_psi_avg_sizes[0] = 1;
    c13_psi_avg_sizes[1] = 1;
    c13_b_psi_avg = c13_psi_avg_sizes[0];
    c13_c_psi_avg = c13_psi_avg_sizes[1];
    c13_psi_avg_data[0] = c13_yc_y;
    _SFD_SYMBOL_SWITCH(15U, 53U);
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 171U);
    c13_h_A = (c13_psi_l[(int32_T)c13_i - 1] + c13_psi_l[(int32_T)c13_i + 2637])
      + c13_psi_l[(int32_T)c13_i + 5275];
    c13_db_x = c13_h_A;
    c13_eb_x = c13_db_x;
    c13_ad_y = c13_eb_x / 3.0;
    c13_psi_l_avg_sizes[0] = 1;
    c13_psi_l_avg_sizes[1] = 1;
    c13_b_psi_l_avg = c13_psi_l_avg_sizes[0];
    c13_c_psi_l_avg = c13_psi_l_avg_sizes[1];
    c13_psi_l_avg_data[0] = c13_ad_y;
    _SFD_SYMBOL_SWITCH(16U, 54U);
    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 173U);
    c13_pc_a = -c13_z_m;
    for (c13_i49 = 0; c13_i49 < 3; c13_i49++) {
      c13_qb_b[c13_i49] = c13_area[c13_i49];
    }

    for (c13_i50 = 0; c13_i50 < 3; c13_i50++) {
      c13_p_HS[c13_i50] = c13_pc_a * c13_qb_b[c13_i50];
    }

    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 174U);
    for (c13_i51 = 0; c13_i51 < 3; c13_i51++) {
      c13_qb_b[c13_i51] = c13_area[c13_i51];
    }

    c13_b_sizes[0] = 1;
    c13_b_sizes[1] = 1;
    c13_rb_b = c13_b_sizes[0];
    c13_sb_b = c13_b_sizes[1];
    c13_loop_ub = c13_psi_avg_sizes[0] * c13_psi_avg_sizes[1] - 1;
    for (c13_i52 = 0; c13_i52 <= c13_loop_ub; c13_i52++) {
      c13_b_data[c13_i52] = c13_psi_avg_data[c13_i52];
    }

    c13_y_sizes[0] = 3;
    c13_y_sizes[1] = 1;
    for (c13_i53 = 0; c13_i53 < 3; c13_i53++) {
      c13_y_data[c13_i53] = c13_qb_b[c13_i53] * c13_b_data[0];
    }

    c13_qc_a = c13_k;
    c13_b_sizes[0] = 1;
    c13_b_sizes[1] = 1;
    c13_tb_b = c13_b_sizes[0];
    c13_ub_b = c13_b_sizes[1];
    c13_b_loop_ub = c13_psi_avg_sizes[0] * c13_psi_avg_sizes[1] - 1;
    for (c13_i54 = 0; c13_i54 <= c13_b_loop_ub; c13_i54++) {
      c13_b_data[c13_i54] = (c13_z_m + c13_psi_avg_data[c13_i54]) + c13_d;
    }

    c13_b_sizes[0] = 1;
    c13_b_sizes[1] = 1;
    c13_vb_b = c13_b_sizes[0];
    c13_wb_b = c13_b_sizes[1];
    c13_xb_b = c13_b_sizes[0];
    c13_yb_b = c13_b_sizes[1];
    c13_c_loop_ub = c13_xb_b * c13_yb_b - 1;
    for (c13_i55 = 0; c13_i55 <= c13_c_loop_ub; c13_i55++) {
      c13_b_data[c13_i55] *= c13_qc_a;
    }

    c13_b_cosh(chartInstance, c13_b_data, c13_b_sizes);
    c13_b_y_sizes[0] = 3;
    c13_b_y_sizes[1] = 1;
    for (c13_i56 = 0; c13_i56 < 3; c13_i56++) {
      c13_b_y_data[c13_i56] = c13_y_data[c13_i56] * c13_b_data[0];
    }

    c13_rc_a = c13_k;
    c13_ac_b = c13_d;
    c13_bd_y = c13_rc_a * c13_ac_b;
    c13_fb_x = c13_bd_y;
    c13_gb_x = c13_fb_x;
    c13_gb_x = muDoubleScalarCosh(c13_gb_x);
    c13_B = c13_gb_x;
    c13_cd_y = c13_B;
    c13_dd_y = c13_cd_y;
    c13_p_FK_sizes[0] = 3;
    c13_p_FK_sizes[1] = 1;
    c13_p_FK = c13_p_FK_sizes[0];
    c13_b_p_FK = c13_p_FK_sizes[1];
    c13_d_loop_ub = c13_b_y_sizes[0] * c13_b_y_sizes[1] - 1;
    for (c13_i57 = 0; c13_i57 <= c13_d_loop_ub; c13_i57++) {
      c13_p_FK_data[c13_i57] = c13_b_y_data[c13_i57] / c13_dd_y;
    }

    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 175U);
    for (c13_i58 = 0; c13_i58 < 3; c13_i58++) {
      c13_qb_b[c13_i58] = c13_area_l[c13_i58];
    }

    c13_b_sizes[0] = 1;
    c13_b_sizes[1] = 1;
    c13_bc_b = c13_b_sizes[0];
    c13_cc_b = c13_b_sizes[1];
    c13_e_loop_ub = c13_psi_l_avg_sizes[0] * c13_psi_l_avg_sizes[1] - 1;
    for (c13_i59 = 0; c13_i59 <= c13_e_loop_ub; c13_i59++) {
      c13_b_data[c13_i59] = c13_psi_l_avg_data[c13_i59];
    }

    c13_y_sizes[0] = 3;
    c13_y_sizes[1] = 1;
    for (c13_i60 = 0; c13_i60 < 3; c13_i60++) {
      c13_y_data[c13_i60] = c13_qb_b[c13_i60] * c13_b_data[0];
    }

    c13_sc_a = c13_k;
    c13_b_sizes[0] = 1;
    c13_b_sizes[1] = 1;
    c13_dc_b = c13_b_sizes[0];
    c13_ec_b = c13_b_sizes[1];
    c13_f_loop_ub = c13_psi_l_avg_sizes[0] * c13_psi_l_avg_sizes[1] - 1;
    for (c13_i61 = 0; c13_i61 <= c13_f_loop_ub; c13_i61++) {
      c13_b_data[c13_i61] = (c13_z_m_l + c13_psi_l_avg_data[c13_i61]) + c13_d;
    }

    c13_b_sizes[0] = 1;
    c13_b_sizes[1] = 1;
    c13_fc_b = c13_b_sizes[0];
    c13_gc_b = c13_b_sizes[1];
    c13_hc_b = c13_b_sizes[0];
    c13_ic_b = c13_b_sizes[1];
    c13_g_loop_ub = c13_hc_b * c13_ic_b - 1;
    for (c13_i62 = 0; c13_i62 <= c13_g_loop_ub; c13_i62++) {
      c13_b_data[c13_i62] *= c13_sc_a;
    }

    c13_b_cosh(chartInstance, c13_b_data, c13_b_sizes);
    c13_b_y_sizes[0] = 3;
    c13_b_y_sizes[1] = 1;
    for (c13_i63 = 0; c13_i63 < 3; c13_i63++) {
      c13_b_y_data[c13_i63] = c13_y_data[c13_i63] * c13_b_data[0];
    }

    c13_tc_a = c13_k;
    c13_jc_b = c13_d;
    c13_ed_y = c13_tc_a * c13_jc_b;
    c13_hb_x = c13_ed_y;
    c13_ib_x = c13_hb_x;
    c13_ib_x = muDoubleScalarCosh(c13_ib_x);
    c13_b_B = c13_ib_x;
    c13_fd_y = c13_b_B;
    c13_gd_y = c13_fd_y;
    c13_p_FK_l_sizes[0] = 3;
    c13_p_FK_l_sizes[1] = 1;
    c13_p_FK_l = c13_p_FK_l_sizes[0];
    c13_b_p_FK_l = c13_p_FK_l_sizes[1];
    c13_h_loop_ub = c13_b_y_sizes[0] * c13_b_y_sizes[1] - 1;
    for (c13_i64 = 0; c13_i64 <= c13_h_loop_ub; c13_i64++) {
      c13_p_FK_l_data[c13_i64] = c13_b_y_data[c13_i64] / c13_gd_y;
    }

    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 176U);
    for (c13_i65 = 0; c13_i65 < 3; c13_i65++) {
      c13_p_total[c13_i65] = (c13_p_HS[c13_i65] + c13_p_FK_data[c13_i65]) -
        c13_p_FK_l_data[c13_i65];
    }

    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 178U);
    for (c13_i66 = 0; c13_i66 < 3; c13_i66++) {
      c13_BodyForce[c13_i66] += c13_p_total[c13_i66];
    }

    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 179U);
    for (c13_i67 = 0; c13_i67 < 3; c13_i67++) {
      c13_b_r_m[c13_i67] = c13_r_m[c13_i67];
    }

    for (c13_i68 = 0; c13_i68 < 3; c13_i68++) {
      c13_b_p_total[c13_i68] = c13_p_total[c13_i68];
    }

    c13_cross(chartInstance, c13_b_r_m, c13_b_p_total, c13_dv8);
    for (c13_i69 = 0; c13_i69 < 3; c13_i69++) {
      c13_PanelMoment[c13_i69] = c13_dv8[c13_i69];
    }

    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 180U);
    for (c13_i70 = 0; c13_i70 < 3; c13_i70++) {
      c13_BodyMoment[c13_i70] += c13_PanelMoment[c13_i70];
    }

    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 182U);
    for (c13_i71 = 0; c13_i71 < 3; c13_i71++) {
      c13_p_FK_total[c13_i71] += c13_p_FK_data[c13_i71];
    }

    _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, 183U);
    for (c13_i72 = 0; c13_i72 < 3; c13_i72++) {
      c13_p_FK_l_total[c13_i72] += c13_p_FK_l_data[c13_i72];
    }

    c13_h_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 6, 0);
  _SFD_EML_CALL(0U, chartInstance->c13_sfEvent, -183);
  _SFD_SYMBOL_SCOPE_POP();
  for (c13_i73 = 0; c13_i73 < 3; c13_i73++) {
    (*c13_b_BodyForce)[c13_i73] = c13_BodyForce[c13_i73];
  }

  for (c13_i74 = 0; c13_i74 < 3; c13_i74++) {
    (*c13_b_BodyMoment)[c13_i74] = c13_BodyMoment[c13_i74];
  }

  *c13_b_psi_m = c13_psi_m;
  for (c13_i75 = 0; c13_i75 < 3; c13_i75++) {
    (*c13_b_p_FK_total)[c13_i75] = c13_p_FK_total[c13_i75];
  }

  for (c13_i76 = 0; c13_i76 < 3; c13_i76++) {
    (*c13_b_p_FK_l_total)[c13_i76] = c13_p_FK_l_total[c13_i76];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c13_sfEvent);
}

static void initSimStructsc13_WEC_Sim_Driver(SFc13_WEC_Sim_DriverInstanceStruct *
  chartInstance)
{
}

static void registerMessagesc13_WEC_Sim_Driver
  (SFc13_WEC_Sim_DriverInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c13_machineNumber, uint32_T
  c13_chartNumber)
{
}

static const mxArray *c13_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  int32_T c13_i77;
  real_T c13_b_inData[3];
  int32_T c13_i78;
  real_T c13_u[3];
  const mxArray *c13_y = NULL;
  SFc13_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc13_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  for (c13_i77 = 0; c13_i77 < 3; c13_i77++) {
    c13_b_inData[c13_i77] = (*(real_T (*)[3])c13_inData)[c13_i77];
  }

  for (c13_i78 = 0; c13_i78 < 3; c13_i78++) {
    c13_u[c13_i78] = c13_b_inData[c13_i78];
  }

  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", c13_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, FALSE);
  return c13_mxArrayOutData;
}

static void c13_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_p_FK_l_total, const char_T *c13_identifier,
  real_T c13_y[3])
{
  emlrtMsgIdentifier c13_thisId;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_p_FK_l_total),
    &c13_thisId, c13_y);
  sf_mex_destroy(&c13_p_FK_l_total);
}

static void c13_b_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId,
  real_T c13_y[3])
{
  real_T c13_dv9[3];
  int32_T c13_i79;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), c13_dv9, 1, 0, 0U, 1, 0U, 1, 3);
  for (c13_i79 = 0; c13_i79 < 3; c13_i79++) {
    c13_y[c13_i79] = c13_dv9[c13_i79];
  }

  sf_mex_destroy(&c13_u);
}

static void c13_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData)
{
  const mxArray *c13_p_FK_l_total;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  real_T c13_y[3];
  int32_T c13_i80;
  SFc13_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc13_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c13_p_FK_l_total = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_p_FK_l_total),
    &c13_thisId, c13_y);
  sf_mex_destroy(&c13_p_FK_l_total);
  for (c13_i80 = 0; c13_i80 < 3; c13_i80++) {
    (*(real_T (*)[3])c13_outData)[c13_i80] = c13_y[c13_i80];
  }

  sf_mex_destroy(&c13_mxArrayInData);
}

static const mxArray *c13_b_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  real_T c13_u;
  const mxArray *c13_y = NULL;
  SFc13_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc13_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  c13_u = *(real_T *)c13_inData;
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", &c13_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, FALSE);
  return c13_mxArrayOutData;
}

static real_T c13_c_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_psi_m, const char_T *c13_identifier)
{
  real_T c13_y;
  emlrtMsgIdentifier c13_thisId;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_y = c13_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_psi_m),
    &c13_thisId);
  sf_mex_destroy(&c13_psi_m);
  return c13_y;
}

static real_T c13_d_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId)
{
  real_T c13_y;
  real_T c13_d0;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), &c13_d0, 1, 0, 0U, 0, 0U, 0);
  c13_y = c13_d0;
  sf_mex_destroy(&c13_u);
  return c13_y;
}

static void c13_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData)
{
  const mxArray *c13_psi_m;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  real_T c13_y;
  SFc13_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc13_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c13_psi_m = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_y = c13_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_psi_m),
    &c13_thisId);
  sf_mex_destroy(&c13_psi_m);
  *(real_T *)c13_outData = c13_y;
  sf_mex_destroy(&c13_mxArrayInData);
}

static const mxArray *c13_c_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  int32_T c13_i81;
  real_T c13_b_inData[4];
  int32_T c13_i82;
  real_T c13_u[4];
  const mxArray *c13_y = NULL;
  SFc13_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc13_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  for (c13_i81 = 0; c13_i81 < 4; c13_i81++) {
    c13_b_inData[c13_i81] = (*(real_T (*)[4])c13_inData)[c13_i81];
  }

  for (c13_i82 = 0; c13_i82 < 4; c13_i82++) {
    c13_u[c13_i82] = c13_b_inData[c13_i82];
  }

  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", c13_u, 0, 0U, 1U, 0U, 2, 4, 1), FALSE);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, FALSE);
  return c13_mxArrayOutData;
}

static const mxArray *c13_d_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  int32_T c13_i83;
  real_T c13_b_inData[6];
  int32_T c13_i84;
  real_T c13_u[6];
  const mxArray *c13_y = NULL;
  SFc13_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc13_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  for (c13_i83 = 0; c13_i83 < 6; c13_i83++) {
    c13_b_inData[c13_i83] = (*(real_T (*)[6])c13_inData)[c13_i83];
  }

  for (c13_i84 = 0; c13_i84 < 6; c13_i84++) {
    c13_u[c13_i84] = c13_b_inData[c13_i84];
  }

  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", c13_u, 0, 0U, 1U, 0U, 1, 6), FALSE);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, FALSE);
  return c13_mxArrayOutData;
}

static const mxArray *c13_e_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  int32_T c13_i85;
  int32_T c13_i86;
  int32_T c13_i87;
  int32_T c13_i88;
  int32_T c13_i89;
  static real_T c13_b_inData[23742];
  int32_T c13_i90;
  int32_T c13_i91;
  int32_T c13_i92;
  int32_T c13_i93;
  int32_T c13_i94;
  real_T c13_u[23742];
  const mxArray *c13_y = NULL;
  SFc13_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc13_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  c13_i85 = 0;
  for (c13_i86 = 0; c13_i86 < 3; c13_i86++) {
    c13_i87 = 0;
    for (c13_i88 = 0; c13_i88 < 3; c13_i88++) {
      for (c13_i89 = 0; c13_i89 < 2638; c13_i89++) {
        c13_b_inData[(c13_i89 + c13_i87) + c13_i85] = (*(real_T (*)[23742])
          c13_inData)[(c13_i89 + c13_i87) + c13_i85];
      }

      c13_i87 += 2638;
    }

    c13_i85 += 7914;
  }

  c13_i90 = 0;
  for (c13_i91 = 0; c13_i91 < 3; c13_i91++) {
    c13_i92 = 0;
    for (c13_i93 = 0; c13_i93 < 3; c13_i93++) {
      for (c13_i94 = 0; c13_i94 < 2638; c13_i94++) {
        c13_u[(c13_i94 + c13_i92) + c13_i90] = c13_b_inData[(c13_i94 + c13_i92)
          + c13_i90];
      }

      c13_i92 += 2638;
    }

    c13_i90 += 7914;
  }

  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", c13_u, 0, 0U, 1U, 0U, 3, 2638, 3, 3),
                FALSE);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, FALSE);
  return c13_mxArrayOutData;
}

static const mxArray *c13_f_sf_marshallOut(void *chartInstanceVoid, real_T
  c13_inData_data[1], int32_T c13_inData_sizes[2])
{
  const mxArray *c13_mxArrayOutData = NULL;
  int32_T c13_b_inData_sizes[2];
  real_T c13_b_inData_data[1];
  int32_T c13_u_sizes[2];
  real_T c13_u_data[1];
  const mxArray *c13_y = NULL;
  SFc13_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc13_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  c13_b_inData_sizes[0] = 1;
  c13_b_inData_sizes[1] = 1;
  c13_b_inData_data[0] = c13_inData_data[0];
  c13_u_sizes[0] = 1;
  c13_u_sizes[1] = 1;
  c13_u_data[0] = c13_b_inData_data[0];
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", c13_u_data, 0, 0U, 1U, 0U, 2,
    c13_u_sizes[0], c13_u_sizes[1]), FALSE);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, FALSE);
  return c13_mxArrayOutData;
}

static void c13_e_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId,
  real_T c13_y_data[1], int32_T c13_y_sizes[2])
{
  int32_T c13_i95;
  uint32_T c13_uv0[2];
  int32_T c13_i96;
  boolean_T c13_bv0[2];
  int32_T c13_tmp_sizes[2];
  real_T c13_tmp_data[1];
  int32_T c13_y;
  int32_T c13_b_y;
  int32_T c13_loop_ub;
  int32_T c13_i97;
  for (c13_i95 = 0; c13_i95 < 2; c13_i95++) {
    c13_uv0[c13_i95] = 1U;
  }

  for (c13_i96 = 0; c13_i96 < 2; c13_i96++) {
    c13_bv0[c13_i96] = FALSE;
  }

  sf_mex_import_vs(c13_parentId, sf_mex_dup(c13_u), c13_tmp_data, 1, 0, 0U, 1,
                   0U, 2, c13_bv0, c13_uv0, c13_tmp_sizes);
  c13_y_sizes[0] = 1;
  c13_y_sizes[1] = 1;
  c13_y = c13_y_sizes[0];
  c13_b_y = c13_y_sizes[1];
  c13_loop_ub = c13_tmp_sizes[0] * c13_tmp_sizes[1] - 1;
  for (c13_i97 = 0; c13_i97 <= c13_loop_ub; c13_i97++) {
    c13_y_data[c13_i97] = c13_tmp_data[c13_i97];
  }

  sf_mex_destroy(&c13_u);
}

static void c13_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, real_T c13_outData_data[1],
  int32_T c13_outData_sizes[2])
{
  const mxArray *c13_psi_l_avg;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  int32_T c13_y_sizes[2];
  real_T c13_y_data[1];
  SFc13_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc13_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c13_psi_l_avg = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_psi_l_avg), &c13_thisId,
    c13_y_data, c13_y_sizes);
  sf_mex_destroy(&c13_psi_l_avg);
  c13_outData_sizes[0] = 1;
  c13_outData_sizes[1] = 1;
  c13_outData_data[0] = c13_y_data[0];
  sf_mex_destroy(&c13_mxArrayInData);
}

static const mxArray *c13_g_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  int32_T c13_i98;
  real_T c13_b_inData[3];
  int32_T c13_i99;
  real_T c13_u[3];
  const mxArray *c13_y = NULL;
  SFc13_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc13_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  for (c13_i98 = 0; c13_i98 < 3; c13_i98++) {
    c13_b_inData[c13_i98] = (*(real_T (*)[3])c13_inData)[c13_i98];
  }

  for (c13_i99 = 0; c13_i99 < 3; c13_i99++) {
    c13_u[c13_i99] = c13_b_inData[c13_i99];
  }

  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", c13_u, 0, 0U, 1U, 0U, 2, 3, 1), FALSE);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, FALSE);
  return c13_mxArrayOutData;
}

static void c13_f_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId,
  real_T c13_y[3])
{
  real_T c13_dv10[3];
  int32_T c13_i100;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), c13_dv10, 1, 0, 0U, 1, 0U, 2, 3,
                1);
  for (c13_i100 = 0; c13_i100 < 3; c13_i100++) {
    c13_y[c13_i100] = c13_dv10[c13_i100];
  }

  sf_mex_destroy(&c13_u);
}

static void c13_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData)
{
  const mxArray *c13_p_total;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  real_T c13_y[3];
  int32_T c13_i101;
  SFc13_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc13_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c13_p_total = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_p_total), &c13_thisId,
    c13_y);
  sf_mex_destroy(&c13_p_total);
  for (c13_i101 = 0; c13_i101 < 3; c13_i101++) {
    (*(real_T (*)[3])c13_outData)[c13_i101] = c13_y[c13_i101];
  }

  sf_mex_destroy(&c13_mxArrayInData);
}

static const mxArray *c13_h_sf_marshallOut(void *chartInstanceVoid, real_T
  c13_inData_data[3], int32_T c13_inData_sizes[2])
{
  const mxArray *c13_mxArrayOutData = NULL;
  int32_T c13_b_inData_sizes[2];
  int32_T c13_i102;
  real_T c13_b_inData_data[3];
  int32_T c13_u_sizes[2];
  int32_T c13_i103;
  real_T c13_u_data[3];
  const mxArray *c13_y = NULL;
  SFc13_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc13_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  c13_b_inData_sizes[0] = 3;
  c13_b_inData_sizes[1] = 1;
  for (c13_i102 = 0; c13_i102 < 3; c13_i102++) {
    c13_b_inData_data[c13_i102] = c13_inData_data[c13_i102];
  }

  c13_u_sizes[0] = 3;
  c13_u_sizes[1] = 1;
  for (c13_i103 = 0; c13_i103 < 3; c13_i103++) {
    c13_u_data[c13_i103] = c13_b_inData_data[c13_i103];
  }

  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", c13_u_data, 0, 0U, 1U, 0U, 2,
    c13_u_sizes[0], c13_u_sizes[1]), FALSE);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, FALSE);
  return c13_mxArrayOutData;
}

static void c13_g_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId,
  real_T c13_y_data[3], int32_T c13_y_sizes[2])
{
  int32_T c13_i104;
  static uint32_T c13_uv1[2] = { 3U, 1U };

  uint32_T c13_uv2[2];
  int32_T c13_i105;
  boolean_T c13_bv1[2];
  int32_T c13_tmp_sizes[2];
  real_T c13_tmp_data[3];
  int32_T c13_y;
  int32_T c13_b_y;
  int32_T c13_loop_ub;
  int32_T c13_i106;
  for (c13_i104 = 0; c13_i104 < 2; c13_i104++) {
    c13_uv2[c13_i104] = c13_uv1[c13_i104];
  }

  for (c13_i105 = 0; c13_i105 < 2; c13_i105++) {
    c13_bv1[c13_i105] = FALSE;
  }

  sf_mex_import_vs(c13_parentId, sf_mex_dup(c13_u), c13_tmp_data, 1, 0, 0U, 1,
                   0U, 2, c13_bv1, c13_uv2, c13_tmp_sizes);
  c13_y_sizes[0] = 3;
  c13_y_sizes[1] = 1;
  c13_y = c13_y_sizes[0];
  c13_b_y = c13_y_sizes[1];
  c13_loop_ub = c13_tmp_sizes[0] * c13_tmp_sizes[1] - 1;
  for (c13_i106 = 0; c13_i106 <= c13_loop_ub; c13_i106++) {
    c13_y_data[c13_i106] = c13_tmp_data[c13_i106];
  }

  sf_mex_destroy(&c13_u);
}

static void c13_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, real_T c13_outData_data[3],
  int32_T c13_outData_sizes[2])
{
  const mxArray *c13_p_FK_l;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  int32_T c13_y_sizes[2];
  real_T c13_y_data[3];
  int32_T c13_i107;
  SFc13_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc13_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c13_p_FK_l = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_p_FK_l), &c13_thisId,
    c13_y_data, c13_y_sizes);
  sf_mex_destroy(&c13_p_FK_l);
  c13_outData_sizes[0] = 3;
  c13_outData_sizes[1] = 1;
  for (c13_i107 = 0; c13_i107 < 3; c13_i107++) {
    c13_outData_data[c13_i107] = c13_y_data[c13_i107];
  }

  sf_mex_destroy(&c13_mxArrayInData);
}

static const mxArray *c13_i_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  int32_T c13_i108;
  real_T c13_b_inData[3];
  int32_T c13_i109;
  real_T c13_u[3];
  const mxArray *c13_y = NULL;
  SFc13_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc13_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  for (c13_i108 = 0; c13_i108 < 3; c13_i108++) {
    c13_b_inData[c13_i108] = (*(real_T (*)[3])c13_inData)[c13_i108];
  }

  for (c13_i109 = 0; c13_i109 < 3; c13_i109++) {
    c13_u[c13_i109] = c13_b_inData[c13_i109];
  }

  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", c13_u, 0, 0U, 1U, 0U, 2, 1, 3), FALSE);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, FALSE);
  return c13_mxArrayOutData;
}

static void c13_h_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId,
  real_T c13_y[3])
{
  real_T c13_dv11[3];
  int32_T c13_i110;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), c13_dv11, 1, 0, 0U, 1, 0U, 2, 1,
                3);
  for (c13_i110 = 0; c13_i110 < 3; c13_i110++) {
    c13_y[c13_i110] = c13_dv11[c13_i110];
  }

  sf_mex_destroy(&c13_u);
}

static void c13_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData)
{
  const mxArray *c13_q;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  real_T c13_y[3];
  int32_T c13_i111;
  SFc13_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc13_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c13_q = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_q), &c13_thisId, c13_y);
  sf_mex_destroy(&c13_q);
  for (c13_i111 = 0; c13_i111 < 3; c13_i111++) {
    (*(real_T (*)[3])c13_outData)[c13_i111] = c13_y[c13_i111];
  }

  sf_mex_destroy(&c13_mxArrayInData);
}

static void c13_i_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId,
  real_T c13_y[23742])
{
  real_T c13_dv12[23742];
  int32_T c13_i112;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), c13_dv12, 1, 0, 0U, 1, 0U, 3,
                2638, 3, 3);
  for (c13_i112 = 0; c13_i112 < 23742; c13_i112++) {
    c13_y[c13_i112] = c13_dv12[c13_i112];
  }

  sf_mex_destroy(&c13_u);
}

static void c13_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData)
{
  const mxArray *c13_STL_l;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  static real_T c13_y[23742];
  int32_T c13_i113;
  int32_T c13_i114;
  int32_T c13_i115;
  int32_T c13_i116;
  int32_T c13_i117;
  SFc13_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc13_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c13_STL_l = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_STL_l), &c13_thisId,
    c13_y);
  sf_mex_destroy(&c13_STL_l);
  c13_i113 = 0;
  for (c13_i114 = 0; c13_i114 < 3; c13_i114++) {
    c13_i115 = 0;
    for (c13_i116 = 0; c13_i116 < 3; c13_i116++) {
      for (c13_i117 = 0; c13_i117 < 2638; c13_i117++) {
        (*(real_T (*)[23742])c13_outData)[(c13_i117 + c13_i115) + c13_i113] =
          c13_y[(c13_i117 + c13_i115) + c13_i113];
      }

      c13_i115 += 2638;
    }

    c13_i113 += 7914;
  }

  sf_mex_destroy(&c13_mxArrayInData);
}

static const mxArray *c13_j_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  int32_T c13_i118;
  int32_T c13_i119;
  int32_T c13_i120;
  real_T c13_b_inData[7914];
  int32_T c13_i121;
  int32_T c13_i122;
  int32_T c13_i123;
  real_T c13_u[7914];
  const mxArray *c13_y = NULL;
  SFc13_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc13_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  c13_i118 = 0;
  for (c13_i119 = 0; c13_i119 < 3; c13_i119++) {
    for (c13_i120 = 0; c13_i120 < 2638; c13_i120++) {
      c13_b_inData[c13_i120 + c13_i118] = (*(real_T (*)[7914])c13_inData)
        [c13_i120 + c13_i118];
    }

    c13_i118 += 2638;
  }

  c13_i121 = 0;
  for (c13_i122 = 0; c13_i122 < 3; c13_i122++) {
    for (c13_i123 = 0; c13_i123 < 2638; c13_i123++) {
      c13_u[c13_i123 + c13_i121] = c13_b_inData[c13_i123 + c13_i121];
    }

    c13_i121 += 2638;
  }

  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", c13_u, 0, 0U, 1U, 0U, 2, 2638, 3),
                FALSE);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, FALSE);
  return c13_mxArrayOutData;
}

static void c13_j_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId,
  real_T c13_y[7914])
{
  real_T c13_dv13[7914];
  int32_T c13_i124;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), c13_dv13, 1, 0, 0U, 1, 0U, 2,
                2638, 3);
  for (c13_i124 = 0; c13_i124 < 7914; c13_i124++) {
    c13_y[c13_i124] = c13_dv13[c13_i124];
  }

  sf_mex_destroy(&c13_u);
}

static void c13_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData)
{
  const mxArray *c13_psi_l_avg;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  real_T c13_y[7914];
  int32_T c13_i125;
  int32_T c13_i126;
  int32_T c13_i127;
  SFc13_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc13_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c13_psi_l_avg = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_psi_l_avg), &c13_thisId,
    c13_y);
  sf_mex_destroy(&c13_psi_l_avg);
  c13_i125 = 0;
  for (c13_i126 = 0; c13_i126 < 3; c13_i126++) {
    for (c13_i127 = 0; c13_i127 < 2638; c13_i127++) {
      (*(real_T (*)[7914])c13_outData)[c13_i127 + c13_i125] = c13_y[c13_i127 +
        c13_i125];
    }

    c13_i125 += 2638;
  }

  sf_mex_destroy(&c13_mxArrayInData);
}

const mxArray *sf_c13_WEC_Sim_Driver_get_eml_resolved_functions_info(void)
{
  const mxArray *c13_nameCaptureInfo;
  c13_ResolvedFunctionInfo c13_info[31];
  const mxArray *c13_m0 = NULL;
  int32_T c13_i128;
  c13_ResolvedFunctionInfo *c13_r0;
  c13_nameCaptureInfo = NULL;
  c13_nameCaptureInfo = NULL;
  c13_info_helper(c13_info);
  sf_mex_assign(&c13_m0, sf_mex_createstruct("nameCaptureInfo", 1, 31), FALSE);
  for (c13_i128 = 0; c13_i128 < 31; c13_i128++) {
    c13_r0 = &c13_info[c13_i128];
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo", c13_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c13_r0->context)), "context", "nameCaptureInfo",
                    c13_i128);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo", c13_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c13_r0->name)), "name", "nameCaptureInfo",
                    c13_i128);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo",
      c13_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c13_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c13_i128);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo", c13_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c13_r0->resolved)), "resolved",
                    "nameCaptureInfo", c13_i128);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo", &c13_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c13_i128);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo", &c13_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c13_i128);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo",
      &c13_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c13_i128);
    sf_mex_addfield(c13_m0, sf_mex_create("nameCaptureInfo",
      &c13_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c13_i128);
  }

  sf_mex_assign(&c13_nameCaptureInfo, c13_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c13_nameCaptureInfo);
  return c13_nameCaptureInfo;
}

static void c13_info_helper(c13_ResolvedFunctionInfo c13_info[31])
{
  c13_info[0].context = "";
  c13_info[0].name = "mtimes";
  c13_info[0].dominantType = "double";
  c13_info[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c13_info[0].fileTimeLo = 1289548492U;
  c13_info[0].fileTimeHi = 0U;
  c13_info[0].mFileTimeLo = 0U;
  c13_info[0].mFileTimeHi = 0U;
  c13_info[1].context = "";
  c13_info[1].name = "cos";
  c13_info[1].dominantType = "double";
  c13_info[1].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c13_info[1].fileTimeLo = 1343859172U;
  c13_info[1].fileTimeHi = 0U;
  c13_info[1].mFileTimeLo = 0U;
  c13_info[1].mFileTimeHi = 0U;
  c13_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c13_info[2].name = "eml_scalar_cos";
  c13_info[2].dominantType = "double";
  c13_info[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c13_info[2].fileTimeLo = 1286847522U;
  c13_info[2].fileTimeHi = 0U;
  c13_info[2].mFileTimeLo = 0U;
  c13_info[2].mFileTimeHi = 0U;
  c13_info[3].context = "";
  c13_info[3].name = "sin";
  c13_info[3].dominantType = "double";
  c13_info[3].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c13_info[3].fileTimeLo = 1343859186U;
  c13_info[3].fileTimeHi = 0U;
  c13_info[3].mFileTimeLo = 0U;
  c13_info[3].mFileTimeHi = 0U;
  c13_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c13_info[4].name = "eml_scalar_sin";
  c13_info[4].dominantType = "double";
  c13_info[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c13_info[4].fileTimeLo = 1286847536U;
  c13_info[4].fileTimeHi = 0U;
  c13_info[4].mFileTimeLo = 0U;
  c13_info[4].mFileTimeHi = 0U;
  c13_info[5].context = "";
  c13_info[5].name = "mrdivide";
  c13_info[5].dominantType = "double";
  c13_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c13_info[5].fileTimeLo = 1357980348U;
  c13_info[5].fileTimeHi = 0U;
  c13_info[5].mFileTimeLo = 1319758766U;
  c13_info[5].mFileTimeHi = 0U;
  c13_info[6].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c13_info[6].name = "rdivide";
  c13_info[6].dominantType = "double";
  c13_info[6].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c13_info[6].fileTimeLo = 1346539188U;
  c13_info[6].fileTimeHi = 0U;
  c13_info[6].mFileTimeLo = 0U;
  c13_info[6].mFileTimeHi = 0U;
  c13_info[7].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c13_info[7].name = "eml_scalexp_compatible";
  c13_info[7].dominantType = "double";
  c13_info[7].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  c13_info[7].fileTimeLo = 1286847596U;
  c13_info[7].fileTimeHi = 0U;
  c13_info[7].mFileTimeLo = 0U;
  c13_info[7].mFileTimeHi = 0U;
  c13_info[8].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c13_info[8].name = "eml_div";
  c13_info[8].dominantType = "double";
  c13_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c13_info[8].fileTimeLo = 1313376610U;
  c13_info[8].fileTimeHi = 0U;
  c13_info[8].mFileTimeLo = 0U;
  c13_info[8].mFileTimeHi = 0U;
  c13_info[9].context = "";
  c13_info[9].name = "cross";
  c13_info[9].dominantType = "double";
  c13_info[9].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c13_info[9].fileTimeLo = 1286847642U;
  c13_info[9].fileTimeHi = 0U;
  c13_info[9].mFileTimeLo = 0U;
  c13_info[9].mFileTimeHi = 0U;
  c13_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/specfun/cross.m";
  c13_info[10].name = "mtimes";
  c13_info[10].dominantType = "double";
  c13_info[10].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c13_info[10].fileTimeLo = 1289548492U;
  c13_info[10].fileTimeHi = 0U;
  c13_info[10].mFileTimeLo = 0U;
  c13_info[10].mFileTimeHi = 0U;
  c13_info[11].context = "";
  c13_info[11].name = "cosh";
  c13_info[11].dominantType = "double";
  c13_info[11].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cosh.m";
  c13_info[11].fileTimeLo = 1343859174U;
  c13_info[11].fileTimeHi = 0U;
  c13_info[11].mFileTimeLo = 0U;
  c13_info[11].mFileTimeHi = 0U;
  c13_info[12].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cosh.m";
  c13_info[12].name = "eml_scalar_cosh";
  c13_info[12].dominantType = "double";
  c13_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cosh.m";
  c13_info[12].fileTimeLo = 1286847522U;
  c13_info[12].fileTimeHi = 0U;
  c13_info[12].mFileTimeLo = 0U;
  c13_info[12].mFileTimeHi = 0U;
  c13_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c13_info[13].name = "eml_index_class";
  c13_info[13].dominantType = "";
  c13_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c13_info[13].fileTimeLo = 1323199378U;
  c13_info[13].fileTimeHi = 0U;
  c13_info[13].mFileTimeLo = 0U;
  c13_info[13].mFileTimeHi = 0U;
  c13_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c13_info[14].name = "eml_scalar_eg";
  c13_info[14].dominantType = "double";
  c13_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c13_info[14].fileTimeLo = 1286847596U;
  c13_info[14].fileTimeHi = 0U;
  c13_info[14].mFileTimeLo = 0U;
  c13_info[14].mFileTimeHi = 0U;
  c13_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c13_info[15].name = "eml_xgemm";
  c13_info[15].dominantType = "char";
  c13_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c13_info[15].fileTimeLo = 1299105572U;
  c13_info[15].fileTimeHi = 0U;
  c13_info[15].mFileTimeLo = 0U;
  c13_info[15].mFileTimeHi = 0U;
  c13_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c13_info[16].name = "eml_blas_inline";
  c13_info[16].dominantType = "";
  c13_info[16].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c13_info[16].fileTimeLo = 1299105568U;
  c13_info[16].fileTimeHi = 0U;
  c13_info[16].mFileTimeLo = 0U;
  c13_info[16].mFileTimeHi = 0U;
  c13_info[17].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c13_info[17].name = "eml_index_class";
  c13_info[17].dominantType = "";
  c13_info[17].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c13_info[17].fileTimeLo = 1323199378U;
  c13_info[17].fileTimeHi = 0U;
  c13_info[17].mFileTimeLo = 0U;
  c13_info[17].mFileTimeHi = 0U;
  c13_info[18].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c13_info[18].name = "eml_scalar_eg";
  c13_info[18].dominantType = "double";
  c13_info[18].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c13_info[18].fileTimeLo = 1286847596U;
  c13_info[18].fileTimeHi = 0U;
  c13_info[18].mFileTimeLo = 0U;
  c13_info[18].mFileTimeHi = 0U;
  c13_info[19].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c13_info[19].name = "eml_refblas_xgemm";
  c13_info[19].dominantType = "char";
  c13_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c13_info[19].fileTimeLo = 1299105574U;
  c13_info[19].fileTimeHi = 0U;
  c13_info[19].mFileTimeLo = 0U;
  c13_info[19].mFileTimeHi = 0U;
  c13_info[20].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c13_info[20].name = "eml_index_minus";
  c13_info[20].dominantType = "double";
  c13_info[20].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c13_info[20].fileTimeLo = 1286847578U;
  c13_info[20].fileTimeHi = 0U;
  c13_info[20].mFileTimeLo = 0U;
  c13_info[20].mFileTimeHi = 0U;
  c13_info[21].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c13_info[21].name = "eml_index_class";
  c13_info[21].dominantType = "";
  c13_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c13_info[21].fileTimeLo = 1323199378U;
  c13_info[21].fileTimeHi = 0U;
  c13_info[21].mFileTimeLo = 0U;
  c13_info[21].mFileTimeHi = 0U;
  c13_info[22].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c13_info[22].name = "eml_index_class";
  c13_info[22].dominantType = "";
  c13_info[22].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c13_info[22].fileTimeLo = 1323199378U;
  c13_info[22].fileTimeHi = 0U;
  c13_info[22].mFileTimeLo = 0U;
  c13_info[22].mFileTimeHi = 0U;
  c13_info[23].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c13_info[23].name = "eml_scalar_eg";
  c13_info[23].dominantType = "double";
  c13_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c13_info[23].fileTimeLo = 1286847596U;
  c13_info[23].fileTimeHi = 0U;
  c13_info[23].mFileTimeLo = 0U;
  c13_info[23].mFileTimeHi = 0U;
  c13_info[24].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c13_info[24].name = "eml_index_times";
  c13_info[24].dominantType = "coder.internal.indexInt";
  c13_info[24].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c13_info[24].fileTimeLo = 1286847580U;
  c13_info[24].fileTimeHi = 0U;
  c13_info[24].mFileTimeLo = 0U;
  c13_info[24].mFileTimeHi = 0U;
  c13_info[25].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m";
  c13_info[25].name = "eml_index_class";
  c13_info[25].dominantType = "";
  c13_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c13_info[25].fileTimeLo = 1323199378U;
  c13_info[25].fileTimeHi = 0U;
  c13_info[25].mFileTimeLo = 0U;
  c13_info[25].mFileTimeHi = 0U;
  c13_info[26].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c13_info[26].name = "eml_index_plus";
  c13_info[26].dominantType = "coder.internal.indexInt";
  c13_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c13_info[26].fileTimeLo = 1286847578U;
  c13_info[26].fileTimeHi = 0U;
  c13_info[26].mFileTimeLo = 0U;
  c13_info[26].mFileTimeHi = 0U;
  c13_info[27].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c13_info[27].name = "eml_index_class";
  c13_info[27].dominantType = "";
  c13_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c13_info[27].fileTimeLo = 1323199378U;
  c13_info[27].fileTimeHi = 0U;
  c13_info[27].mFileTimeLo = 0U;
  c13_info[27].mFileTimeHi = 0U;
  c13_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c13_info[28].name = "eml_int_forloop_overflow_check";
  c13_info[28].dominantType = "";
  c13_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c13_info[28].fileTimeLo = 1346539140U;
  c13_info[28].fileTimeHi = 0U;
  c13_info[28].mFileTimeLo = 0U;
  c13_info[28].mFileTimeHi = 0U;
  c13_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c13_info[29].name = "intmax";
  c13_info[29].dominantType = "char";
  c13_info[29].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m";
  c13_info[29].fileTimeLo = 1311284116U;
  c13_info[29].fileTimeHi = 0U;
  c13_info[29].mFileTimeLo = 0U;
  c13_info[29].mFileTimeHi = 0U;
  c13_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c13_info[30].name = "eml_index_plus";
  c13_info[30].dominantType = "double";
  c13_info[30].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c13_info[30].fileTimeLo = 1286847578U;
  c13_info[30].fileTimeHi = 0U;
  c13_info[30].mFileTimeLo = 0U;
  c13_info[30].mFileTimeHi = 0U;
}

static void c13_cross(SFc13_WEC_Sim_DriverInstanceStruct *chartInstance, real_T
                      c13_a[3], real_T c13_b[3], real_T c13_c[3])
{
  real_T c13_b_a;
  real_T c13_b_b;
  real_T c13_y;
  real_T c13_c_a;
  real_T c13_c_b;
  real_T c13_b_y;
  real_T c13_c1;
  real_T c13_d_a;
  real_T c13_d_b;
  real_T c13_c_y;
  real_T c13_e_a;
  real_T c13_e_b;
  real_T c13_d_y;
  real_T c13_c2;
  real_T c13_f_a;
  real_T c13_f_b;
  real_T c13_e_y;
  real_T c13_g_a;
  real_T c13_g_b;
  real_T c13_f_y;
  real_T c13_c3;
  c13_b_a = c13_a[1];
  c13_b_b = c13_b[2];
  c13_y = c13_b_a * c13_b_b;
  c13_c_a = c13_a[2];
  c13_c_b = c13_b[1];
  c13_b_y = c13_c_a * c13_c_b;
  c13_c1 = c13_y - c13_b_y;
  c13_d_a = c13_a[2];
  c13_d_b = c13_b[0];
  c13_c_y = c13_d_a * c13_d_b;
  c13_e_a = c13_a[0];
  c13_e_b = c13_b[2];
  c13_d_y = c13_e_a * c13_e_b;
  c13_c2 = c13_c_y - c13_d_y;
  c13_f_a = c13_a[0];
  c13_f_b = c13_b[1];
  c13_e_y = c13_f_a * c13_f_b;
  c13_g_a = c13_a[1];
  c13_g_b = c13_b[0];
  c13_f_y = c13_g_a * c13_g_b;
  c13_c3 = c13_e_y - c13_f_y;
  c13_c[0] = c13_c1;
  c13_c[1] = c13_c2;
  c13_c[2] = c13_c3;
}

static void c13_cosh(SFc13_WEC_Sim_DriverInstanceStruct *chartInstance, real_T
                     c13_x_data[1], int32_T c13_x_sizes[2], real_T c13_b_x_data
                     [1], int32_T c13_b_x_sizes[2])
{
  int32_T c13_x;
  int32_T c13_b_x;
  int32_T c13_loop_ub;
  int32_T c13_i129;
  c13_b_x_sizes[0] = 1;
  c13_b_x_sizes[1] = 1;
  c13_x = c13_b_x_sizes[0];
  c13_b_x = c13_b_x_sizes[1];
  c13_loop_ub = c13_x_sizes[0] * c13_x_sizes[1] - 1;
  for (c13_i129 = 0; c13_i129 <= c13_loop_ub; c13_i129++) {
    c13_b_x_data[c13_i129] = c13_x_data[c13_i129];
  }

  c13_b_cosh(chartInstance, c13_b_x_data, c13_b_x_sizes);
}

static const mxArray *c13_k_sf_marshallOut(void *chartInstanceVoid, void
  *c13_inData)
{
  const mxArray *c13_mxArrayOutData = NULL;
  int32_T c13_u;
  const mxArray *c13_y = NULL;
  SFc13_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc13_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c13_mxArrayOutData = NULL;
  c13_u = *(int32_T *)c13_inData;
  c13_y = NULL;
  sf_mex_assign(&c13_y, sf_mex_create("y", &c13_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c13_mxArrayOutData, c13_y, FALSE);
  return c13_mxArrayOutData;
}

static int32_T c13_k_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId)
{
  int32_T c13_y;
  int32_T c13_i130;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), &c13_i130, 1, 6, 0U, 0, 0U, 0);
  c13_y = c13_i130;
  sf_mex_destroy(&c13_u);
  return c13_y;
}

static void c13_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c13_mxArrayInData, const char_T *c13_varName, void *c13_outData)
{
  const mxArray *c13_b_sfEvent;
  const char_T *c13_identifier;
  emlrtMsgIdentifier c13_thisId;
  int32_T c13_y;
  SFc13_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc13_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c13_b_sfEvent = sf_mex_dup(c13_mxArrayInData);
  c13_identifier = c13_varName;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_y = c13_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c13_b_sfEvent),
    &c13_thisId);
  sf_mex_destroy(&c13_b_sfEvent);
  *(int32_T *)c13_outData = c13_y;
  sf_mex_destroy(&c13_mxArrayInData);
}

static uint8_T c13_l_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_b_is_active_c13_WEC_Sim_Driver, const
  char_T *c13_identifier)
{
  uint8_T c13_y;
  emlrtMsgIdentifier c13_thisId;
  c13_thisId.fIdentifier = c13_identifier;
  c13_thisId.fParent = NULL;
  c13_y = c13_m_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c13_b_is_active_c13_WEC_Sim_Driver), &c13_thisId);
  sf_mex_destroy(&c13_b_is_active_c13_WEC_Sim_Driver);
  return c13_y;
}

static uint8_T c13_m_emlrt_marshallIn(SFc13_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c13_u, const emlrtMsgIdentifier *c13_parentId)
{
  uint8_T c13_y;
  uint8_T c13_u0;
  sf_mex_import(c13_parentId, sf_mex_dup(c13_u), &c13_u0, 1, 3, 0U, 0, 0U, 0);
  c13_y = c13_u0;
  sf_mex_destroy(&c13_u);
  return c13_y;
}

static void c13_b_cosh(SFc13_WEC_Sim_DriverInstanceStruct *chartInstance, real_T
  c13_x_data[1], int32_T c13_x_sizes[2])
{
  int32_T c13_k;
  real_T c13_x;
  real_T c13_b_x;
  c13_k = 0;
  while (c13_k <= 0) {
    c13_x = c13_x_data[0];
    c13_b_x = c13_x;
    c13_b_x = muDoubleScalarCosh(c13_b_x);
    c13_x_data[0] = c13_b_x;
    c13_k = 1;
  }
}

static void init_dsm_address_info(SFc13_WEC_Sim_DriverInstanceStruct
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

void sf_c13_WEC_Sim_Driver_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1176985866U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2894912978U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(15409138U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1288280201U);
}

mxArray *sf_c13_WEC_Sim_Driver_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("w3czBlvhNSLPGkuQykYn2D");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

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

mxArray *sf_c13_WEC_Sim_Driver_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c13_WEC_Sim_Driver(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x6'type','srcId','name','auxInfo'{{M[1],M[5],T\"BodyForce\",},{M[1],M[10],T\"BodyMoment\",},{M[1],M[18],T\"p_FK_l_total\",},{M[1],M[17],T\"p_FK_total\",},{M[1],M[16],T\"psi_m\",},{M[8],M[0],T\"is_active_c13_WEC_Sim_Driver\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 6, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c13_WEC_Sim_Driver_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc13_WEC_Sim_DriverInstanceStruct *chartInstance;
    chartInstance = (SFc13_WEC_Sim_DriverInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _WEC_Sim_DriverMachineNumber_,
           13,
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
          _SFD_SET_DATA_PROPS(3,1,1,0,"Disp2");
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,7177);
        _SFD_CV_INIT_EML_IF(0,1,0,1495,1508,-1,1544);
        _SFD_CV_INIT_EML_IF(0,1,1,1864,1883,-1,1934);
        _SFD_CV_INIT_EML_IF(0,1,2,1991,2008,-1,3166);
        _SFD_CV_INIT_EML_IF(0,1,3,3175,3192,-1,3256);
        _SFD_CV_INIT_EML_IF(0,1,4,3370,3387,4540,4684);
        _SFD_CV_INIT_EML_IF(0,1,5,4795,4813,-1,4854);
        _SFD_CV_INIT_EML_FOR(0,1,0,1299,1311,1660);
        _SFD_CV_INIT_EML_FOR(0,1,1,1315,1327,1656);
        _SFD_CV_INIT_EML_FOR(0,1,2,1731,1743,3268);
        _SFD_CV_INIT_EML_FOR(0,1,3,1747,1759,3264);
        _SFD_CV_INIT_EML_FOR(0,1,4,3270,3282,5044);
        _SFD_CV_INIT_EML_FOR(0,1,5,3286,3298,5040);
        _SFD_CV_INIT_EML_FOR(0,1,6,5187,5199,7105);
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
            1.0,0,0,(MexFcnForType)c13_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c13_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)
            c13_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c13_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)
            c13_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 4;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c13_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c13_b_sf_marshallOut,(MexInFcnForType)
          c13_b_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)
            c13_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c13_sf_marshallOut,(MexInFcnForType)
            c13_sf_marshallIn);
        }

        {
          real_T *c13_t;
          real_T *c13_psi_m;
          real_T (*c13_STL)[23742];
          real_T (*c13_BodyForce)[3];
          real_T (*c13_Disp2)[6];
          real_T (*c13_BodyMoment)[3];
          real_T (*c13_nonlinear_params)[4];
          real_T (*c13_p_FK_total)[3];
          real_T (*c13_p_FK_l_total)[3];
          c13_p_FK_l_total = (real_T (*)[3])ssGetOutputPortSignal
            (chartInstance->S, 5);
          c13_p_FK_total = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
            4);
          c13_psi_m = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
          c13_nonlinear_params = (real_T (*)[4])ssGetInputPortSignal
            (chartInstance->S, 3);
          c13_BodyMoment = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
            2);
          c13_Disp2 = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 2);
          c13_BodyForce = (real_T (*)[3])ssGetOutputPortSignal(chartInstance->S,
            1);
          c13_t = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c13_STL = (real_T (*)[23742])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c13_STL);
          _SFD_SET_DATA_VALUE_PTR(1U, c13_t);
          _SFD_SET_DATA_VALUE_PTR(2U, *c13_BodyForce);
          _SFD_SET_DATA_VALUE_PTR(3U, *c13_Disp2);
          _SFD_SET_DATA_VALUE_PTR(4U, *c13_BodyMoment);
          _SFD_SET_DATA_VALUE_PTR(5U, *c13_nonlinear_params);
          _SFD_SET_DATA_VALUE_PTR(6U, c13_psi_m);
          _SFD_SET_DATA_VALUE_PTR(7U, *c13_p_FK_total);
          _SFD_SET_DATA_VALUE_PTR(8U, *c13_p_FK_l_total);
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
  return "K59nuLBnEe70lgx8mLgwfB";
}

static void sf_opaque_initialize_c13_WEC_Sim_Driver(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc13_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c13_WEC_Sim_Driver((SFc13_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar);
  initialize_c13_WEC_Sim_Driver((SFc13_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c13_WEC_Sim_Driver(void *chartInstanceVar)
{
  enable_c13_WEC_Sim_Driver((SFc13_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c13_WEC_Sim_Driver(void *chartInstanceVar)
{
  disable_c13_WEC_Sim_Driver((SFc13_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c13_WEC_Sim_Driver(void *chartInstanceVar)
{
  sf_c13_WEC_Sim_Driver((SFc13_WEC_Sim_DriverInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c13_WEC_Sim_Driver(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c13_WEC_Sim_Driver
    ((SFc13_WEC_Sim_DriverInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c13_WEC_Sim_Driver();/* state var info */
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

extern void sf_internal_set_sim_state_c13_WEC_Sim_Driver(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c13_WEC_Sim_Driver();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c13_WEC_Sim_Driver((SFc13_WEC_Sim_DriverInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c13_WEC_Sim_Driver(SimStruct* S)
{
  return sf_internal_get_sim_state_c13_WEC_Sim_Driver(S);
}

static void sf_opaque_set_sim_state_c13_WEC_Sim_Driver(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c13_WEC_Sim_Driver(S, st);
}

static void sf_opaque_terminate_c13_WEC_Sim_Driver(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc13_WEC_Sim_DriverInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_WEC_Sim_Driver_optimization_info();
    }

    finalize_c13_WEC_Sim_Driver((SFc13_WEC_Sim_DriverInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc13_WEC_Sim_Driver((SFc13_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c13_WEC_Sim_Driver(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c13_WEC_Sim_Driver((SFc13_WEC_Sim_DriverInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c13_WEC_Sim_Driver(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_WEC_Sim_Driver_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      13);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,13,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,13,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,13);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,13,4);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,13,5);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,13);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1657063319U));
  ssSetChecksum1(S,(910039024U));
  ssSetChecksum2(S,(2753942718U));
  ssSetChecksum3(S,(3819572480U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c13_WEC_Sim_Driver(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c13_WEC_Sim_Driver(SimStruct *S)
{
  SFc13_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc13_WEC_Sim_DriverInstanceStruct *)utMalloc(sizeof
    (SFc13_WEC_Sim_DriverInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc13_WEC_Sim_DriverInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c13_WEC_Sim_Driver;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c13_WEC_Sim_Driver;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c13_WEC_Sim_Driver;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c13_WEC_Sim_Driver;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c13_WEC_Sim_Driver;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c13_WEC_Sim_Driver;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c13_WEC_Sim_Driver;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c13_WEC_Sim_Driver;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c13_WEC_Sim_Driver;
  chartInstance->chartInfo.mdlStart = mdlStart_c13_WEC_Sim_Driver;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c13_WEC_Sim_Driver;
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

void c13_WEC_Sim_Driver_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c13_WEC_Sim_Driver(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c13_WEC_Sim_Driver(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c13_WEC_Sim_Driver(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c13_WEC_Sim_Driver_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
