/* Include files */

#include <stddef.h>
#include "blas.h"
#include "WEC_Sim_Driver_sfun.h"
#include "c11_WEC_Sim_Driver.h"
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
static const char * c11_debug_family_names[7] = { "int", "nargin", "nargout",
  "t", "deltaT", "matrix", "F" };

/* Function Declarations */
static void initialize_c11_WEC_Sim_Driver(SFc11_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void initialize_params_c11_WEC_Sim_Driver
  (SFc11_WEC_Sim_DriverInstanceStruct *chartInstance);
static void enable_c11_WEC_Sim_Driver(SFc11_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void disable_c11_WEC_Sim_Driver(SFc11_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void c11_update_debugger_state_c11_WEC_Sim_Driver
  (SFc11_WEC_Sim_DriverInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c11_WEC_Sim_Driver
  (SFc11_WEC_Sim_DriverInstanceStruct *chartInstance);
static void set_sim_state_c11_WEC_Sim_Driver(SFc11_WEC_Sim_DriverInstanceStruct *
  chartInstance, const mxArray *c11_st);
static void finalize_c11_WEC_Sim_Driver(SFc11_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void sf_c11_WEC_Sim_Driver(SFc11_WEC_Sim_DriverInstanceStruct
  *chartInstance);
static void initSimStructsc11_WEC_Sim_Driver(SFc11_WEC_Sim_DriverInstanceStruct *
  chartInstance);
static void registerMessagesc11_WEC_Sim_Driver
  (SFc11_WEC_Sim_DriverInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c11_machineNumber, uint32_T
  c11_chartNumber);
static const mxArray *c11_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData);
static void c11_emlrt_marshallIn(SFc11_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c11_F, const char_T *c11_identifier, real_T
  c11_y[6]);
static void c11_b_emlrt_marshallIn(SFc11_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId,
  real_T c11_y[6]);
static void c11_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData);
static const mxArray *c11_b_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData);
static const mxArray *c11_c_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData);
static real_T c11_c_emlrt_marshallIn(SFc11_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId);
static void c11_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData);
static const mxArray *c11_d_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData);
static int32_T c11_d_emlrt_marshallIn(SFc11_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId);
static void c11_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData);
static uint8_T c11_e_emlrt_marshallIn(SFc11_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c11_b_is_active_c11_WEC_Sim_Driver, const
  char_T *c11_identifier);
static uint8_T c11_f_emlrt_marshallIn(SFc11_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId);
static void init_dsm_address_info(SFc11_WEC_Sim_DriverInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c11_WEC_Sim_Driver(SFc11_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
  chartInstance->c11_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c11_is_active_c11_WEC_Sim_Driver = 0U;
}

static void initialize_params_c11_WEC_Sim_Driver
  (SFc11_WEC_Sim_DriverInstanceStruct *chartInstance)
{
}

static void enable_c11_WEC_Sim_Driver(SFc11_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c11_WEC_Sim_Driver(SFc11_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c11_update_debugger_state_c11_WEC_Sim_Driver
  (SFc11_WEC_Sim_DriverInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c11_WEC_Sim_Driver
  (SFc11_WEC_Sim_DriverInstanceStruct *chartInstance)
{
  const mxArray *c11_st;
  const mxArray *c11_y = NULL;
  int32_T c11_i0;
  real_T c11_u[6];
  const mxArray *c11_b_y = NULL;
  uint8_T c11_hoistedGlobal;
  uint8_T c11_b_u;
  const mxArray *c11_c_y = NULL;
  real_T (*c11_F)[6];
  c11_F = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  c11_st = NULL;
  c11_st = NULL;
  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_createcellarray(2), FALSE);
  for (c11_i0 = 0; c11_i0 < 6; c11_i0++) {
    c11_u[c11_i0] = (*c11_F)[c11_i0];
  }

  c11_b_y = NULL;
  sf_mex_assign(&c11_b_y, sf_mex_create("y", c11_u, 0, 0U, 1U, 0U, 1, 6), FALSE);
  sf_mex_setcell(c11_y, 0, c11_b_y);
  c11_hoistedGlobal = chartInstance->c11_is_active_c11_WEC_Sim_Driver;
  c11_b_u = c11_hoistedGlobal;
  c11_c_y = NULL;
  sf_mex_assign(&c11_c_y, sf_mex_create("y", &c11_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c11_y, 1, c11_c_y);
  sf_mex_assign(&c11_st, c11_y, FALSE);
  return c11_st;
}

static void set_sim_state_c11_WEC_Sim_Driver(SFc11_WEC_Sim_DriverInstanceStruct *
  chartInstance, const mxArray *c11_st)
{
  const mxArray *c11_u;
  real_T c11_dv0[6];
  int32_T c11_i1;
  real_T (*c11_F)[6];
  c11_F = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c11_doneDoubleBufferReInit = TRUE;
  c11_u = sf_mex_dup(c11_st);
  c11_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c11_u, 0)), "F",
                       c11_dv0);
  for (c11_i1 = 0; c11_i1 < 6; c11_i1++) {
    (*c11_F)[c11_i1] = c11_dv0[c11_i1];
  }

  chartInstance->c11_is_active_c11_WEC_Sim_Driver = c11_e_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c11_u, 1)),
     "is_active_c11_WEC_Sim_Driver");
  sf_mex_destroy(&c11_u);
  c11_update_debugger_state_c11_WEC_Sim_Driver(chartInstance);
  sf_mex_destroy(&c11_st);
}

static void finalize_c11_WEC_Sim_Driver(SFc11_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
}

static void sf_c11_WEC_Sim_Driver(SFc11_WEC_Sim_DriverInstanceStruct
  *chartInstance)
{
  int32_T c11_i2;
  int32_T c11_i3;
  real_T c11_hoistedGlobal;
  real_T c11_b_hoistedGlobal;
  real_T c11_t;
  real_T c11_deltaT;
  int32_T c11_i4;
  real_T c11_matrix[24006];
  uint32_T c11_debug_family_var_map[7];
  real_T c11_int;
  real_T c11_nargin = 3.0;
  real_T c11_nargout = 1.0;
  real_T c11_F[6];
  real_T c11_A;
  real_T c11_B;
  real_T c11_x;
  real_T c11_y;
  real_T c11_b_x;
  real_T c11_b_y;
  real_T c11_c_y;
  real_T c11_c_x;
  real_T c11_d_x;
  int32_T c11_b_int;
  int32_T c11_i5;
  int32_T c11_i6;
  real_T *c11_b_deltaT;
  real_T *c11_b_t;
  real_T (*c11_b_F)[6];
  real_T (*c11_b_matrix)[24006];
  c11_b_matrix = (real_T (*)[24006])ssGetInputPortSignal(chartInstance->S, 2);
  c11_b_deltaT = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c11_b_F = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
  c11_b_t = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 7U, chartInstance->c11_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c11_b_t, 0U);
  for (c11_i2 = 0; c11_i2 < 6; c11_i2++) {
    _SFD_DATA_RANGE_CHECK((*c11_b_F)[c11_i2], 1U);
  }

  _SFD_DATA_RANGE_CHECK(*c11_b_deltaT, 2U);
  for (c11_i3 = 0; c11_i3 < 24006; c11_i3++) {
    _SFD_DATA_RANGE_CHECK((*c11_b_matrix)[c11_i3], 3U);
  }

  chartInstance->c11_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 7U, chartInstance->c11_sfEvent);
  c11_hoistedGlobal = *c11_b_t;
  c11_b_hoistedGlobal = *c11_b_deltaT;
  c11_t = c11_hoistedGlobal;
  c11_deltaT = c11_b_hoistedGlobal;
  for (c11_i4 = 0; c11_i4 < 24006; c11_i4++) {
    c11_matrix[c11_i4] = (*c11_b_matrix)[c11_i4];
  }

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 7U, 7U, c11_debug_family_names,
    c11_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_int, 0U, c11_c_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_nargin, 1U, c11_c_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c11_nargout, 2U, c11_c_sf_marshallOut,
    c11_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c11_t, 3U, c11_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c11_deltaT, 4U, c11_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c11_matrix, 5U, c11_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c11_F, 6U, c11_sf_marshallOut,
    c11_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 3);
  c11_A = c11_t;
  c11_B = c11_deltaT;
  c11_x = c11_A;
  c11_y = c11_B;
  c11_b_x = c11_x;
  c11_b_y = c11_y;
  c11_c_y = c11_b_x / c11_b_y;
  c11_c_x = c11_c_y + 1.0;
  c11_int = c11_c_x;
  c11_d_x = c11_int;
  c11_int = c11_d_x;
  c11_int = muDoubleScalarRound(c11_int);
  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, 4);
  c11_b_int = (int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("matrix", (int32_T)
    _SFD_INTEGER_CHECK("int", c11_int), 1, 4001, 1, 0) - 1;
  for (c11_i5 = 0; c11_i5 < 6; c11_i5++) {
    c11_F[c11_i5] = c11_matrix[c11_b_int + 4001 * c11_i5];
  }

  _SFD_EML_CALL(0U, chartInstance->c11_sfEvent, -4);
  _SFD_SYMBOL_SCOPE_POP();
  for (c11_i6 = 0; c11_i6 < 6; c11_i6++) {
    (*c11_b_F)[c11_i6] = c11_F[c11_i6];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c11_sfEvent);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_WEC_Sim_DriverMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc11_WEC_Sim_Driver(SFc11_WEC_Sim_DriverInstanceStruct *
  chartInstance)
{
}

static void registerMessagesc11_WEC_Sim_Driver
  (SFc11_WEC_Sim_DriverInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c11_machineNumber, uint32_T
  c11_chartNumber)
{
}

static const mxArray *c11_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData)
{
  const mxArray *c11_mxArrayOutData = NULL;
  int32_T c11_i7;
  real_T c11_b_inData[6];
  int32_T c11_i8;
  real_T c11_u[6];
  const mxArray *c11_y = NULL;
  SFc11_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc11_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c11_mxArrayOutData = NULL;
  for (c11_i7 = 0; c11_i7 < 6; c11_i7++) {
    c11_b_inData[c11_i7] = (*(real_T (*)[6])c11_inData)[c11_i7];
  }

  for (c11_i8 = 0; c11_i8 < 6; c11_i8++) {
    c11_u[c11_i8] = c11_b_inData[c11_i8];
  }

  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_create("y", c11_u, 0, 0U, 1U, 0U, 1, 6), FALSE);
  sf_mex_assign(&c11_mxArrayOutData, c11_y, FALSE);
  return c11_mxArrayOutData;
}

static void c11_emlrt_marshallIn(SFc11_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c11_F, const char_T *c11_identifier, real_T
  c11_y[6])
{
  emlrtMsgIdentifier c11_thisId;
  c11_thisId.fIdentifier = c11_identifier;
  c11_thisId.fParent = NULL;
  c11_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c11_F), &c11_thisId, c11_y);
  sf_mex_destroy(&c11_F);
}

static void c11_b_emlrt_marshallIn(SFc11_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId,
  real_T c11_y[6])
{
  real_T c11_dv1[6];
  int32_T c11_i9;
  sf_mex_import(c11_parentId, sf_mex_dup(c11_u), c11_dv1, 1, 0, 0U, 1, 0U, 1, 6);
  for (c11_i9 = 0; c11_i9 < 6; c11_i9++) {
    c11_y[c11_i9] = c11_dv1[c11_i9];
  }

  sf_mex_destroy(&c11_u);
}

static void c11_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData)
{
  const mxArray *c11_F;
  const char_T *c11_identifier;
  emlrtMsgIdentifier c11_thisId;
  real_T c11_y[6];
  int32_T c11_i10;
  SFc11_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc11_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c11_F = sf_mex_dup(c11_mxArrayInData);
  c11_identifier = c11_varName;
  c11_thisId.fIdentifier = c11_identifier;
  c11_thisId.fParent = NULL;
  c11_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c11_F), &c11_thisId, c11_y);
  sf_mex_destroy(&c11_F);
  for (c11_i10 = 0; c11_i10 < 6; c11_i10++) {
    (*(real_T (*)[6])c11_outData)[c11_i10] = c11_y[c11_i10];
  }

  sf_mex_destroy(&c11_mxArrayInData);
}

static const mxArray *c11_b_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData)
{
  const mxArray *c11_mxArrayOutData = NULL;
  int32_T c11_i11;
  int32_T c11_i12;
  int32_T c11_i13;
  static real_T c11_b_inData[24006];
  int32_T c11_i14;
  int32_T c11_i15;
  int32_T c11_i16;
  real_T c11_u[24006];
  const mxArray *c11_y = NULL;
  SFc11_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc11_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c11_mxArrayOutData = NULL;
  c11_i11 = 0;
  for (c11_i12 = 0; c11_i12 < 6; c11_i12++) {
    for (c11_i13 = 0; c11_i13 < 4001; c11_i13++) {
      c11_b_inData[c11_i13 + c11_i11] = (*(real_T (*)[24006])c11_inData)[c11_i13
        + c11_i11];
    }

    c11_i11 += 4001;
  }

  c11_i14 = 0;
  for (c11_i15 = 0; c11_i15 < 6; c11_i15++) {
    for (c11_i16 = 0; c11_i16 < 4001; c11_i16++) {
      c11_u[c11_i16 + c11_i14] = c11_b_inData[c11_i16 + c11_i14];
    }

    c11_i14 += 4001;
  }

  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_create("y", c11_u, 0, 0U, 1U, 0U, 2, 4001, 6),
                FALSE);
  sf_mex_assign(&c11_mxArrayOutData, c11_y, FALSE);
  return c11_mxArrayOutData;
}

static const mxArray *c11_c_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData)
{
  const mxArray *c11_mxArrayOutData = NULL;
  real_T c11_u;
  const mxArray *c11_y = NULL;
  SFc11_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc11_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c11_mxArrayOutData = NULL;
  c11_u = *(real_T *)c11_inData;
  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_create("y", &c11_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c11_mxArrayOutData, c11_y, FALSE);
  return c11_mxArrayOutData;
}

static real_T c11_c_emlrt_marshallIn(SFc11_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId)
{
  real_T c11_y;
  real_T c11_d0;
  sf_mex_import(c11_parentId, sf_mex_dup(c11_u), &c11_d0, 1, 0, 0U, 0, 0U, 0);
  c11_y = c11_d0;
  sf_mex_destroy(&c11_u);
  return c11_y;
}

static void c11_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData)
{
  const mxArray *c11_nargout;
  const char_T *c11_identifier;
  emlrtMsgIdentifier c11_thisId;
  real_T c11_y;
  SFc11_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc11_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c11_nargout = sf_mex_dup(c11_mxArrayInData);
  c11_identifier = c11_varName;
  c11_thisId.fIdentifier = c11_identifier;
  c11_thisId.fParent = NULL;
  c11_y = c11_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c11_nargout),
    &c11_thisId);
  sf_mex_destroy(&c11_nargout);
  *(real_T *)c11_outData = c11_y;
  sf_mex_destroy(&c11_mxArrayInData);
}

const mxArray *sf_c11_WEC_Sim_Driver_get_eml_resolved_functions_info(void)
{
  const mxArray *c11_nameCaptureInfo;
  c11_ResolvedFunctionInfo c11_info[6];
  c11_ResolvedFunctionInfo (*c11_b_info)[6];
  const mxArray *c11_m0 = NULL;
  int32_T c11_i17;
  c11_ResolvedFunctionInfo *c11_r0;
  c11_nameCaptureInfo = NULL;
  c11_nameCaptureInfo = NULL;
  c11_b_info = (c11_ResolvedFunctionInfo (*)[6])c11_info;
  (*c11_b_info)[0].context = "";
  (*c11_b_info)[0].name = "mrdivide";
  (*c11_b_info)[0].dominantType = "double";
  (*c11_b_info)[0].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  (*c11_b_info)[0].fileTimeLo = 1357980348U;
  (*c11_b_info)[0].fileTimeHi = 0U;
  (*c11_b_info)[0].mFileTimeLo = 1319758766U;
  (*c11_b_info)[0].mFileTimeHi = 0U;
  (*c11_b_info)[1].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  (*c11_b_info)[1].name = "rdivide";
  (*c11_b_info)[1].dominantType = "double";
  (*c11_b_info)[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c11_b_info)[1].fileTimeLo = 1346539188U;
  (*c11_b_info)[1].fileTimeHi = 0U;
  (*c11_b_info)[1].mFileTimeLo = 0U;
  (*c11_b_info)[1].mFileTimeHi = 0U;
  (*c11_b_info)[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c11_b_info)[2].name = "eml_scalexp_compatible";
  (*c11_b_info)[2].dominantType = "double";
  (*c11_b_info)[2].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m";
  (*c11_b_info)[2].fileTimeLo = 1286847596U;
  (*c11_b_info)[2].fileTimeHi = 0U;
  (*c11_b_info)[2].mFileTimeLo = 0U;
  (*c11_b_info)[2].mFileTimeHi = 0U;
  (*c11_b_info)[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  (*c11_b_info)[3].name = "eml_div";
  (*c11_b_info)[3].dominantType = "double";
  (*c11_b_info)[3].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  (*c11_b_info)[3].fileTimeLo = 1313376610U;
  (*c11_b_info)[3].fileTimeHi = 0U;
  (*c11_b_info)[3].mFileTimeLo = 0U;
  (*c11_b_info)[3].mFileTimeHi = 0U;
  (*c11_b_info)[4].context = "";
  (*c11_b_info)[4].name = "round";
  (*c11_b_info)[4].dominantType = "double";
  (*c11_b_info)[4].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/round.m";
  (*c11_b_info)[4].fileTimeLo = 1343859184U;
  (*c11_b_info)[4].fileTimeHi = 0U;
  (*c11_b_info)[4].mFileTimeLo = 0U;
  (*c11_b_info)[4].mFileTimeHi = 0U;
  (*c11_b_info)[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/round.m";
  (*c11_b_info)[5].name = "eml_scalar_round";
  (*c11_b_info)[5].dominantType = "double";
  (*c11_b_info)[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_round.m";
  (*c11_b_info)[5].fileTimeLo = 1307680038U;
  (*c11_b_info)[5].fileTimeHi = 0U;
  (*c11_b_info)[5].mFileTimeLo = 0U;
  (*c11_b_info)[5].mFileTimeHi = 0U;
  sf_mex_assign(&c11_m0, sf_mex_createstruct("nameCaptureInfo", 1, 6), FALSE);
  for (c11_i17 = 0; c11_i17 < 6; c11_i17++) {
    c11_r0 = &c11_info[c11_i17];
    sf_mex_addfield(c11_m0, sf_mex_create("nameCaptureInfo", c11_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c11_r0->context)), "context", "nameCaptureInfo",
                    c11_i17);
    sf_mex_addfield(c11_m0, sf_mex_create("nameCaptureInfo", c11_r0->name, 15,
      0U, 0U, 0U, 2, 1, strlen(c11_r0->name)), "name", "nameCaptureInfo",
                    c11_i17);
    sf_mex_addfield(c11_m0, sf_mex_create("nameCaptureInfo",
      c11_r0->dominantType, 15, 0U, 0U, 0U, 2, 1, strlen(c11_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c11_i17);
    sf_mex_addfield(c11_m0, sf_mex_create("nameCaptureInfo", c11_r0->resolved,
      15, 0U, 0U, 0U, 2, 1, strlen(c11_r0->resolved)), "resolved",
                    "nameCaptureInfo", c11_i17);
    sf_mex_addfield(c11_m0, sf_mex_create("nameCaptureInfo", &c11_r0->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c11_i17);
    sf_mex_addfield(c11_m0, sf_mex_create("nameCaptureInfo", &c11_r0->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c11_i17);
    sf_mex_addfield(c11_m0, sf_mex_create("nameCaptureInfo",
      &c11_r0->mFileTimeLo, 7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo",
                    c11_i17);
    sf_mex_addfield(c11_m0, sf_mex_create("nameCaptureInfo",
      &c11_r0->mFileTimeHi, 7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo",
                    c11_i17);
  }

  sf_mex_assign(&c11_nameCaptureInfo, c11_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c11_nameCaptureInfo);
  return c11_nameCaptureInfo;
}

static const mxArray *c11_d_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData)
{
  const mxArray *c11_mxArrayOutData = NULL;
  int32_T c11_u;
  const mxArray *c11_y = NULL;
  SFc11_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc11_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c11_mxArrayOutData = NULL;
  c11_u = *(int32_T *)c11_inData;
  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_create("y", &c11_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c11_mxArrayOutData, c11_y, FALSE);
  return c11_mxArrayOutData;
}

static int32_T c11_d_emlrt_marshallIn(SFc11_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId)
{
  int32_T c11_y;
  int32_T c11_i18;
  sf_mex_import(c11_parentId, sf_mex_dup(c11_u), &c11_i18, 1, 6, 0U, 0, 0U, 0);
  c11_y = c11_i18;
  sf_mex_destroy(&c11_u);
  return c11_y;
}

static void c11_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData)
{
  const mxArray *c11_b_sfEvent;
  const char_T *c11_identifier;
  emlrtMsgIdentifier c11_thisId;
  int32_T c11_y;
  SFc11_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc11_WEC_Sim_DriverInstanceStruct *)chartInstanceVoid;
  c11_b_sfEvent = sf_mex_dup(c11_mxArrayInData);
  c11_identifier = c11_varName;
  c11_thisId.fIdentifier = c11_identifier;
  c11_thisId.fParent = NULL;
  c11_y = c11_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c11_b_sfEvent),
    &c11_thisId);
  sf_mex_destroy(&c11_b_sfEvent);
  *(int32_T *)c11_outData = c11_y;
  sf_mex_destroy(&c11_mxArrayInData);
}

static uint8_T c11_e_emlrt_marshallIn(SFc11_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c11_b_is_active_c11_WEC_Sim_Driver, const
  char_T *c11_identifier)
{
  uint8_T c11_y;
  emlrtMsgIdentifier c11_thisId;
  c11_thisId.fIdentifier = c11_identifier;
  c11_thisId.fParent = NULL;
  c11_y = c11_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c11_b_is_active_c11_WEC_Sim_Driver), &c11_thisId);
  sf_mex_destroy(&c11_b_is_active_c11_WEC_Sim_Driver);
  return c11_y;
}

static uint8_T c11_f_emlrt_marshallIn(SFc11_WEC_Sim_DriverInstanceStruct
  *chartInstance, const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId)
{
  uint8_T c11_y;
  uint8_T c11_u0;
  sf_mex_import(c11_parentId, sf_mex_dup(c11_u), &c11_u0, 1, 3, 0U, 0, 0U, 0);
  c11_y = c11_u0;
  sf_mex_destroy(&c11_u);
  return c11_y;
}

static void init_dsm_address_info(SFc11_WEC_Sim_DriverInstanceStruct
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

void sf_c11_WEC_Sim_Driver_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2116391569U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(836947953U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4205370041U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2585803355U);
}

mxArray *sf_c11_WEC_Sim_Driver_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("5j2yfCKNeWBuasz6Sj2pPG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
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
      pr[0] = (double)(4001);
      pr[1] = (double)(6);
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
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c11_WEC_Sim_Driver_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c11_WEC_Sim_Driver(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"F\",},{M[8],M[0],T\"is_active_c11_WEC_Sim_Driver\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c11_WEC_Sim_Driver_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc11_WEC_Sim_DriverInstanceStruct *chartInstance;
    chartInstance = (SFc11_WEC_Sim_DriverInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _WEC_Sim_DriverMachineNumber_,
           11,
           1,
           1,
           4,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"t");
          _SFD_SET_DATA_PROPS(1,2,0,1,"F");
          _SFD_SET_DATA_PROPS(2,1,1,0,"deltaT");
          _SFD_SET_DATA_PROPS(3,1,1,0,"matrix");
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
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,89);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c11_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c11_sf_marshallOut,(MexInFcnForType)
            c11_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c11_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 4001;
          dimVector[1]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c11_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          real_T *c11_t;
          real_T *c11_deltaT;
          real_T (*c11_F)[6];
          real_T (*c11_matrix)[24006];
          c11_matrix = (real_T (*)[24006])ssGetInputPortSignal(chartInstance->S,
            2);
          c11_deltaT = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c11_F = (real_T (*)[6])ssGetOutputPortSignal(chartInstance->S, 1);
          c11_t = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c11_t);
          _SFD_SET_DATA_VALUE_PTR(1U, *c11_F);
          _SFD_SET_DATA_VALUE_PTR(2U, c11_deltaT);
          _SFD_SET_DATA_VALUE_PTR(3U, *c11_matrix);
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
  return "kwmDjIBXng1xlLPFtbirnD";
}

static void sf_opaque_initialize_c11_WEC_Sim_Driver(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc11_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c11_WEC_Sim_Driver((SFc11_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar);
  initialize_c11_WEC_Sim_Driver((SFc11_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c11_WEC_Sim_Driver(void *chartInstanceVar)
{
  enable_c11_WEC_Sim_Driver((SFc11_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c11_WEC_Sim_Driver(void *chartInstanceVar)
{
  disable_c11_WEC_Sim_Driver((SFc11_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c11_WEC_Sim_Driver(void *chartInstanceVar)
{
  sf_c11_WEC_Sim_Driver((SFc11_WEC_Sim_DriverInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c11_WEC_Sim_Driver(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c11_WEC_Sim_Driver
    ((SFc11_WEC_Sim_DriverInstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c11_WEC_Sim_Driver();/* state var info */
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

extern void sf_internal_set_sim_state_c11_WEC_Sim_Driver(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c11_WEC_Sim_Driver();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c11_WEC_Sim_Driver((SFc11_WEC_Sim_DriverInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c11_WEC_Sim_Driver(SimStruct* S)
{
  return sf_internal_get_sim_state_c11_WEC_Sim_Driver(S);
}

static void sf_opaque_set_sim_state_c11_WEC_Sim_Driver(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c11_WEC_Sim_Driver(S, st);
}

static void sf_opaque_terminate_c11_WEC_Sim_Driver(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc11_WEC_Sim_DriverInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_WEC_Sim_Driver_optimization_info();
    }

    finalize_c11_WEC_Sim_Driver((SFc11_WEC_Sim_DriverInstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc11_WEC_Sim_Driver((SFc11_WEC_Sim_DriverInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c11_WEC_Sim_Driver(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c11_WEC_Sim_Driver((SFc11_WEC_Sim_DriverInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c11_WEC_Sim_Driver(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_WEC_Sim_Driver_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      11);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,11,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,11,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,11);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,11,3);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,11,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 3; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,11);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2950836323U));
  ssSetChecksum1(S,(1802132241U));
  ssSetChecksum2(S,(1132581697U));
  ssSetChecksum3(S,(2892979399U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c11_WEC_Sim_Driver(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c11_WEC_Sim_Driver(SimStruct *S)
{
  SFc11_WEC_Sim_DriverInstanceStruct *chartInstance;
  chartInstance = (SFc11_WEC_Sim_DriverInstanceStruct *)utMalloc(sizeof
    (SFc11_WEC_Sim_DriverInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc11_WEC_Sim_DriverInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c11_WEC_Sim_Driver;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c11_WEC_Sim_Driver;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c11_WEC_Sim_Driver;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c11_WEC_Sim_Driver;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c11_WEC_Sim_Driver;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c11_WEC_Sim_Driver;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c11_WEC_Sim_Driver;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c11_WEC_Sim_Driver;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c11_WEC_Sim_Driver;
  chartInstance->chartInfo.mdlStart = mdlStart_c11_WEC_Sim_Driver;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c11_WEC_Sim_Driver;
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

void c11_WEC_Sim_Driver_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c11_WEC_Sim_Driver(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c11_WEC_Sim_Driver(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c11_WEC_Sim_Driver(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c11_WEC_Sim_Driver_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
