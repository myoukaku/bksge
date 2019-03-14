﻿/**
 *	@file	dec.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_PREPROCESSOR_ARITHMETIC_DEC_HPP
#define BKSGE_PREPROCESSOR_ARITHMETIC_DEC_HPP
#
# include <bksge/preprocessor/config/config.hpp>
#
# /* BKSGE_PP_DEC */
#
# if ~BKSGE_PP_CONFIG_FLAGS() & BKSGE_PP_CONFIG_MWCC()
#    define BKSGE_PP_DEC(x) BKSGE_PP_DEC_I(x)
# else
#    define BKSGE_PP_DEC(x) BKSGE_PP_DEC_OO((x))
#    define BKSGE_PP_DEC_OO(par) BKSGE_PP_DEC_I ## par
# endif
#
# define BKSGE_PP_DEC_I(x) BKSGE_PP_DEC_ ## x
#
# define BKSGE_PP_DEC_0 0
# define BKSGE_PP_DEC_1 0
# define BKSGE_PP_DEC_2 1
# define BKSGE_PP_DEC_3 2
# define BKSGE_PP_DEC_4 3
# define BKSGE_PP_DEC_5 4
# define BKSGE_PP_DEC_6 5
# define BKSGE_PP_DEC_7 6
# define BKSGE_PP_DEC_8 7
# define BKSGE_PP_DEC_9 8
# define BKSGE_PP_DEC_10 9
# define BKSGE_PP_DEC_11 10
# define BKSGE_PP_DEC_12 11
# define BKSGE_PP_DEC_13 12
# define BKSGE_PP_DEC_14 13
# define BKSGE_PP_DEC_15 14
# define BKSGE_PP_DEC_16 15
# define BKSGE_PP_DEC_17 16
# define BKSGE_PP_DEC_18 17
# define BKSGE_PP_DEC_19 18
# define BKSGE_PP_DEC_20 19
# define BKSGE_PP_DEC_21 20
# define BKSGE_PP_DEC_22 21
# define BKSGE_PP_DEC_23 22
# define BKSGE_PP_DEC_24 23
# define BKSGE_PP_DEC_25 24
# define BKSGE_PP_DEC_26 25
# define BKSGE_PP_DEC_27 26
# define BKSGE_PP_DEC_28 27
# define BKSGE_PP_DEC_29 28
# define BKSGE_PP_DEC_30 29
# define BKSGE_PP_DEC_31 30
# define BKSGE_PP_DEC_32 31
# define BKSGE_PP_DEC_33 32
# define BKSGE_PP_DEC_34 33
# define BKSGE_PP_DEC_35 34
# define BKSGE_PP_DEC_36 35
# define BKSGE_PP_DEC_37 36
# define BKSGE_PP_DEC_38 37
# define BKSGE_PP_DEC_39 38
# define BKSGE_PP_DEC_40 39
# define BKSGE_PP_DEC_41 40
# define BKSGE_PP_DEC_42 41
# define BKSGE_PP_DEC_43 42
# define BKSGE_PP_DEC_44 43
# define BKSGE_PP_DEC_45 44
# define BKSGE_PP_DEC_46 45
# define BKSGE_PP_DEC_47 46
# define BKSGE_PP_DEC_48 47
# define BKSGE_PP_DEC_49 48
# define BKSGE_PP_DEC_50 49
# define BKSGE_PP_DEC_51 50
# define BKSGE_PP_DEC_52 51
# define BKSGE_PP_DEC_53 52
# define BKSGE_PP_DEC_54 53
# define BKSGE_PP_DEC_55 54
# define BKSGE_PP_DEC_56 55
# define BKSGE_PP_DEC_57 56
# define BKSGE_PP_DEC_58 57
# define BKSGE_PP_DEC_59 58
# define BKSGE_PP_DEC_60 59
# define BKSGE_PP_DEC_61 60
# define BKSGE_PP_DEC_62 61
# define BKSGE_PP_DEC_63 62
# define BKSGE_PP_DEC_64 63
# define BKSGE_PP_DEC_65 64
# define BKSGE_PP_DEC_66 65
# define BKSGE_PP_DEC_67 66
# define BKSGE_PP_DEC_68 67
# define BKSGE_PP_DEC_69 68
# define BKSGE_PP_DEC_70 69
# define BKSGE_PP_DEC_71 70
# define BKSGE_PP_DEC_72 71
# define BKSGE_PP_DEC_73 72
# define BKSGE_PP_DEC_74 73
# define BKSGE_PP_DEC_75 74
# define BKSGE_PP_DEC_76 75
# define BKSGE_PP_DEC_77 76
# define BKSGE_PP_DEC_78 77
# define BKSGE_PP_DEC_79 78
# define BKSGE_PP_DEC_80 79
# define BKSGE_PP_DEC_81 80
# define BKSGE_PP_DEC_82 81
# define BKSGE_PP_DEC_83 82
# define BKSGE_PP_DEC_84 83
# define BKSGE_PP_DEC_85 84
# define BKSGE_PP_DEC_86 85
# define BKSGE_PP_DEC_87 86
# define BKSGE_PP_DEC_88 87
# define BKSGE_PP_DEC_89 88
# define BKSGE_PP_DEC_90 89
# define BKSGE_PP_DEC_91 90
# define BKSGE_PP_DEC_92 91
# define BKSGE_PP_DEC_93 92
# define BKSGE_PP_DEC_94 93
# define BKSGE_PP_DEC_95 94
# define BKSGE_PP_DEC_96 95
# define BKSGE_PP_DEC_97 96
# define BKSGE_PP_DEC_98 97
# define BKSGE_PP_DEC_99 98
# define BKSGE_PP_DEC_100 99
# define BKSGE_PP_DEC_101 100
# define BKSGE_PP_DEC_102 101
# define BKSGE_PP_DEC_103 102
# define BKSGE_PP_DEC_104 103
# define BKSGE_PP_DEC_105 104
# define BKSGE_PP_DEC_106 105
# define BKSGE_PP_DEC_107 106
# define BKSGE_PP_DEC_108 107
# define BKSGE_PP_DEC_109 108
# define BKSGE_PP_DEC_110 109
# define BKSGE_PP_DEC_111 110
# define BKSGE_PP_DEC_112 111
# define BKSGE_PP_DEC_113 112
# define BKSGE_PP_DEC_114 113
# define BKSGE_PP_DEC_115 114
# define BKSGE_PP_DEC_116 115
# define BKSGE_PP_DEC_117 116
# define BKSGE_PP_DEC_118 117
# define BKSGE_PP_DEC_119 118
# define BKSGE_PP_DEC_120 119
# define BKSGE_PP_DEC_121 120
# define BKSGE_PP_DEC_122 121
# define BKSGE_PP_DEC_123 122
# define BKSGE_PP_DEC_124 123
# define BKSGE_PP_DEC_125 124
# define BKSGE_PP_DEC_126 125
# define BKSGE_PP_DEC_127 126
# define BKSGE_PP_DEC_128 127
# define BKSGE_PP_DEC_129 128
# define BKSGE_PP_DEC_130 129
# define BKSGE_PP_DEC_131 130
# define BKSGE_PP_DEC_132 131
# define BKSGE_PP_DEC_133 132
# define BKSGE_PP_DEC_134 133
# define BKSGE_PP_DEC_135 134
# define BKSGE_PP_DEC_136 135
# define BKSGE_PP_DEC_137 136
# define BKSGE_PP_DEC_138 137
# define BKSGE_PP_DEC_139 138
# define BKSGE_PP_DEC_140 139
# define BKSGE_PP_DEC_141 140
# define BKSGE_PP_DEC_142 141
# define BKSGE_PP_DEC_143 142
# define BKSGE_PP_DEC_144 143
# define BKSGE_PP_DEC_145 144
# define BKSGE_PP_DEC_146 145
# define BKSGE_PP_DEC_147 146
# define BKSGE_PP_DEC_148 147
# define BKSGE_PP_DEC_149 148
# define BKSGE_PP_DEC_150 149
# define BKSGE_PP_DEC_151 150
# define BKSGE_PP_DEC_152 151
# define BKSGE_PP_DEC_153 152
# define BKSGE_PP_DEC_154 153
# define BKSGE_PP_DEC_155 154
# define BKSGE_PP_DEC_156 155
# define BKSGE_PP_DEC_157 156
# define BKSGE_PP_DEC_158 157
# define BKSGE_PP_DEC_159 158
# define BKSGE_PP_DEC_160 159
# define BKSGE_PP_DEC_161 160
# define BKSGE_PP_DEC_162 161
# define BKSGE_PP_DEC_163 162
# define BKSGE_PP_DEC_164 163
# define BKSGE_PP_DEC_165 164
# define BKSGE_PP_DEC_166 165
# define BKSGE_PP_DEC_167 166
# define BKSGE_PP_DEC_168 167
# define BKSGE_PP_DEC_169 168
# define BKSGE_PP_DEC_170 169
# define BKSGE_PP_DEC_171 170
# define BKSGE_PP_DEC_172 171
# define BKSGE_PP_DEC_173 172
# define BKSGE_PP_DEC_174 173
# define BKSGE_PP_DEC_175 174
# define BKSGE_PP_DEC_176 175
# define BKSGE_PP_DEC_177 176
# define BKSGE_PP_DEC_178 177
# define BKSGE_PP_DEC_179 178
# define BKSGE_PP_DEC_180 179
# define BKSGE_PP_DEC_181 180
# define BKSGE_PP_DEC_182 181
# define BKSGE_PP_DEC_183 182
# define BKSGE_PP_DEC_184 183
# define BKSGE_PP_DEC_185 184
# define BKSGE_PP_DEC_186 185
# define BKSGE_PP_DEC_187 186
# define BKSGE_PP_DEC_188 187
# define BKSGE_PP_DEC_189 188
# define BKSGE_PP_DEC_190 189
# define BKSGE_PP_DEC_191 190
# define BKSGE_PP_DEC_192 191
# define BKSGE_PP_DEC_193 192
# define BKSGE_PP_DEC_194 193
# define BKSGE_PP_DEC_195 194
# define BKSGE_PP_DEC_196 195
# define BKSGE_PP_DEC_197 196
# define BKSGE_PP_DEC_198 197
# define BKSGE_PP_DEC_199 198
# define BKSGE_PP_DEC_200 199
# define BKSGE_PP_DEC_201 200
# define BKSGE_PP_DEC_202 201
# define BKSGE_PP_DEC_203 202
# define BKSGE_PP_DEC_204 203
# define BKSGE_PP_DEC_205 204
# define BKSGE_PP_DEC_206 205
# define BKSGE_PP_DEC_207 206
# define BKSGE_PP_DEC_208 207
# define BKSGE_PP_DEC_209 208
# define BKSGE_PP_DEC_210 209
# define BKSGE_PP_DEC_211 210
# define BKSGE_PP_DEC_212 211
# define BKSGE_PP_DEC_213 212
# define BKSGE_PP_DEC_214 213
# define BKSGE_PP_DEC_215 214
# define BKSGE_PP_DEC_216 215
# define BKSGE_PP_DEC_217 216
# define BKSGE_PP_DEC_218 217
# define BKSGE_PP_DEC_219 218
# define BKSGE_PP_DEC_220 219
# define BKSGE_PP_DEC_221 220
# define BKSGE_PP_DEC_222 221
# define BKSGE_PP_DEC_223 222
# define BKSGE_PP_DEC_224 223
# define BKSGE_PP_DEC_225 224
# define BKSGE_PP_DEC_226 225
# define BKSGE_PP_DEC_227 226
# define BKSGE_PP_DEC_228 227
# define BKSGE_PP_DEC_229 228
# define BKSGE_PP_DEC_230 229
# define BKSGE_PP_DEC_231 230
# define BKSGE_PP_DEC_232 231
# define BKSGE_PP_DEC_233 232
# define BKSGE_PP_DEC_234 233
# define BKSGE_PP_DEC_235 234
# define BKSGE_PP_DEC_236 235
# define BKSGE_PP_DEC_237 236
# define BKSGE_PP_DEC_238 237
# define BKSGE_PP_DEC_239 238
# define BKSGE_PP_DEC_240 239
# define BKSGE_PP_DEC_241 240
# define BKSGE_PP_DEC_242 241
# define BKSGE_PP_DEC_243 242
# define BKSGE_PP_DEC_244 243
# define BKSGE_PP_DEC_245 244
# define BKSGE_PP_DEC_246 245
# define BKSGE_PP_DEC_247 246
# define BKSGE_PP_DEC_248 247
# define BKSGE_PP_DEC_249 248
# define BKSGE_PP_DEC_250 249
# define BKSGE_PP_DEC_251 250
# define BKSGE_PP_DEC_252 251
# define BKSGE_PP_DEC_253 252
# define BKSGE_PP_DEC_254 253
# define BKSGE_PP_DEC_255 254
# define BKSGE_PP_DEC_256 255
# define BKSGE_PP_DEC_257 256
#
#endif // BKSGE_PREPROCESSOR_ARITHMETIC_DEC_HPP
