#ifndef DTF_GF_UNIT_TEST_H_
#define DTF_GF_UNIT_TEST_H_

const int DTF_gf_test_nsamples = 10;
const int DTF_gf_test_vec_len = 32;
#ifdef SOC_C6678
#pragma DATA_SECTION(DTF_gf_test_input_data, ".gsvd_unit_test");
#pragma DATA_ALIGN(DTF_gf_test_input_data, 2);
#endif // SOC_C6678
const float DTF_gf_test_input_data[320] = {(float)1.307016461800319274, 
(float)-1.486402334023405158, 
(float)-0.032526071876446350, 
(float)-0.598762905018848213, 
(float)0.932679288178094978, 
(float)-0.633268242222765898, 
(float)0.803788795048344995, 
(float)-0.764304642938202550, 
(float)1.077398518263431137, 
(float)0.372813597904309291, 
(float)-1.185888176449303444, 
(float)-1.151096179451772006, 
(float)0.056648752202603667, 
(float)-1.978049332852083619, 
(float)0.915747256182275704, 
(float)1.476458710659880991, 
(float)0.661347711364685953, 
(float)-1.147474394601079917, 
(float)0.240485543512003214, 
(float)2.237706460606839975, 
(float)1.257680486727770663, 
(float)0.545797746698097996, 
(float)0.874113845596710348, 
(float)1.343414504616407656, 
(float)0.192075450811297371, 
(float)-0.106516095252761192, 
(float)-0.269776523606211960, 
(float)0.161531743703109271, 
(float)-0.232277995146971866, 
(float)-0.764115812536576566, 
(float)-0.929658429325166402, 
(float)0.607867121940198873, 
(float)-0.565110926172459838, 
(float)-0.941178873692055440, 
(float)-1.371336865749253286, 
(float)-1.373564882523732322, 
(float)0.686608634025200337, 
(float)-0.364054577098681664, 
(float)0.619051052574027261, 
(float)1.215404948900382420, 
(float)-0.266829893075179625, 
(float)0.725452410413562565, 
(float)2.895951670619578699, 
(float)-0.335367293861863480, 
(float)0.447609643222778186, 
(float)-0.305473391165055064, 
(float)1.116947919468707751, 
(float)-0.400223294888481462, 
(float)-0.417153086780036597, 
(float)0.662979290112119091, 
(float)-0.021752773246955789, 
(float)-0.684637128410052975, 
(float)-2.166817125666371968, 
(float)-1.407869600934133381, 
(float)-0.540657329567007183, 
(float)0.788313435143979335, 
(float)0.698926572099257903, 
(float)0.546187075685997891, 
(float)1.027823883602072774, 
(float)-0.199370743170747960, 
(float)0.381571263836441410, 
(float)-0.061854253109076496, 
(float)0.449230726087625931, 
(float)-0.185499561199815338, 
(float)1.032774520093337367, 
(float)-1.561687020527641412, 
(float)2.361924374432637030, 
(float)-0.270255354714994345, 
(float)-1.232105359497789765, 
(float)-1.145029161782524563, 
(float)-0.041268502537395786, 
(float)1.301800091854405039, 
(float)-0.943305734136656970, 
(float)0.419023275577530496, 
(float)-0.825772409956174624, 
(float)0.954672223247917673, 
(float)-0.551670852465968808, 
(float)-0.797514993920238502, 
(float)2.176406653566148375, 
(float)0.279476284441402878, 
(float)1.308206517921735923, 
(float)0.957490789307044232, 
(float)0.210268898691969131, 
(float)1.353401028345141643, 
(float)-0.114082028638196192, 
(float)0.546055556037850609, 
(float)-1.553776754700554319, 
(float)-1.221962741717857348, 
(float)0.765226158648165122, 
(float)-0.354101645477063964, 
(float)-0.410171282213300847, 
(float)0.384241589155241203, 
(float)-2.629051131810939967, 
(float)-0.360302987091546123, 
(float)-1.079872260583285559, 
(float)0.472329274436858348, 
(float)0.030547890842882203, 
(float)-1.532001987085225059, 
(float)-0.099347736692603994, 
(float)-0.225783237119474012, 
(float)0.524337970396697606, 
(float)-0.625699910504679213, 
(float)-1.349490729363457708, 
(float)-0.075575853611495880, 
(float)0.501297166526375126, 
(float)0.360896023286955692, 
(float)0.660595472942341888, 
(float)-0.936747952259016969, 
(float)-0.851919586460179845, 
(float)-0.669131067514653233, 
(float)0.617255113405149047, 
(float)0.283640603624290499, 
(float)0.350975702033897718, 
(float)1.017503914264512588, 
(float)0.677656204983207666, 
(float)-0.174162030842294063, 
(float)0.161605450858557514, 
(float)2.228081536255081652, 
(float)1.441676508240582688, 
(float)-0.448535555941660613, 
(float)-1.864627533176680618, 
(float)-0.392420914284623223, 
(float)0.134230346538702972, 
(float)-1.997634940367013723, 
(float)1.302881330170512442, 
(float)1.419329304090040544, 
(float)-0.011651666636202361, 
(float)-0.392171726620127281, 
(float)0.751405573203866917, 
(float)0.731076745065522227, 
(float)-0.128089904692468087, 
(float)-0.556332072542855438, 
(float)0.257585856427741844, 
(float)1.861490660796562890, 
(float)-1.455026240053099107, 
(float)1.718034129316954317, 
(float)-1.836230319056532556, 
(float)-0.836933877405570792, 
(float)0.574473831529545342, 
(float)1.109509047102451795, 
(float)-0.863486546100649566, 
(float)-0.183800644218742371, 
(float)-0.816181542304018182, 
(float)-1.541216957954832933, 
(float)1.140959998506109851, 
(float)-0.481365257584428330, 
(float)0.030579427495883025, 
(float)2.113024235602654066, 
(float)0.341773192657503222, 
(float)-0.026203407303094374, 
(float)0.720278057718163556, 
(float)0.240319877480641209, 
(float)-1.206410079897086929, 
(float)0.734276072763759058, 
(float)0.008401386045478628, 
(float)-0.088993891477200882, 
(float)0.761916767756440350, 
(float)0.195516516657686046, 
(float)-0.547957129773780416, 
(float)-1.207402673126251935, 
(float)0.651187411856975373, 
(float)0.787447695200398701, 
(float)0.203237318828952768, 
(float)0.091734135618790069, 
(float)-0.089741958607451211, 
(float)-0.118306382680510427, 
(float)-0.210051165071392848, 
(float)1.433591718053010000, 
(float)1.160610460784452069, 
(float)-0.372854435510665494, 
(float)0.739722935971149465, 
(float)-0.579779414277480032, 
(float)-0.716811172175868427, 
(float)-0.122259963901076282, 
(float)0.207273828869760701, 
(float)-0.565466727933411795, 
(float)-1.439219438721567546, 
(float)0.800344587159631859, 
(float)-0.446126222533971328, 
(float)0.022957537993674740, 
(float)0.584728877091598376, 
(float)0.083384840841821309, 
(float)0.022658821210565776, 
(float)0.357492430864183863, 
(float)0.548716483484170903, 
(float)-0.576491757710425712, 
(float)0.352011485351502174, 
(float)0.606728880417395700, 
(float)0.352750607488705070, 
(float)-1.522695532431740384, 
(float)1.147413823766622265, 
(float)-1.040303435981174252, 
(float)1.945256854949581671, 
(float)-0.661415745558265655, 
(float)-0.219558773931690848, 
(float)1.089338966417847887, 
(float)-1.358142777124750955, 
(float)0.463774968999114467, 
(float)0.735676964002657252, 
(float)0.537940096094992048, 
(float)-0.727120669811960441, 
(float)0.455160137179117685, 
(float)-0.979545104025003388, 
(float)0.298804779989578828, 
(float)-0.551777870097639012, 
(float)0.189286298703857020, 
(float)-0.815779355390068184, 
(float)0.413129415102125530, 
(float)-0.491954333875760375, 
(float)-0.851879355131986649, 
(float)-2.206474837230201214, 
(float)0.470551504511946495, 
(float)1.738465278485423537, 
(float)-0.555365702235674163, 
(float)1.438865186519224126, 
(float)-0.184695413593674834, 
(float)-0.812232504926446164, 
(float)0.082637597240386079, 
(float)-0.408265141876974991, 
(float)0.694411222039304721, 
(float)-0.859279601891416056, 
(float)0.129401829050186518, 
(float)0.287771071472969320, 
(float)0.127245036550812873, 
(float)0.286536688100194392, 
(float)-0.423578759249020664, 
(float)-1.478958993054732662, 
(float)0.338076045715417550, 
(float)-0.945626754861264684, 
(float)1.113624454631131577, 
(float)-0.308006250389030067, 
(float)0.862735035730560762, 
(float)1.724262988382105455, 
(float)-0.339354114251800787, 
(float)-0.601782203009850858, 
(float)1.111711455677595106, 
(float)0.316898685552175430, 
(float)0.037282834125835405, 
(float)0.142221565139841494, 
(float)-0.739015778936195078, 
(float)1.049845125281102076, 
(float)-0.459890616030922073, 
(float)1.110109646949122286, 
(float)-0.486149939067994696, 
(float)1.455923012062263489, 
(float)0.297130081287434789, 
(float)-3.102703946701694804, 
(float)-0.182594105676760515, 
(float)1.259967208801379579, 
(float)-0.318866999897946146, 
(float)-0.650639457894271911, 
(float)0.448836746650382756, 
(float)1.464000065119692495, 
(float)0.741926893343006100, 
(float)0.113284436794970869, 
(float)0.515216589102264311, 
(float)0.518330816817544004, 
(float)-0.180146628340177251, 
(float)0.397601842648749482, 
(float)-0.012931279330990241, 
(float)0.701469646050860818, 
(float)0.621093444614376322, 
(float)-1.427542107071435140, 
(float)-0.546930630578256749, 
(float)-1.230503611980243939, 
(float)0.096067913616544057, 
(float)-2.277723871644537823, 
(float)-0.118043652906420035, 
(float)1.058154602581250270, 
(float)0.436294948005208016, 
(float)1.411523668148809696, 
(float)-0.014612171217782537, 
(float)-0.537791437512862847, 
(float)-1.834760967982472568, 
(float)2.635533396520933991, 
(float)0.290773882213948232, 
(float)1.065598644673894757, 
(float)0.535227282602097398, 
(float)-0.387343927846192482, 
(float)-0.319639202651887500, 
(float)-2.524523093987024680, 
(float)-1.006283849705811084, 
(float)-0.424157077177941655, 
(float)-0.661207110677132448, 
(float)0.727567325013973809, 
(float)0.456614179939555664, 
(float)-0.506170698227752403, 
(float)-1.184645587463836192, 
(float)0.781787476001563397, 
(float)-0.080382722424650929, 
(float)0.334162413334626429, 
(float)0.346039913624941076, 
(float)-0.119491833407183362, 
(float)0.716204805449069060, 
(float)0.227944028218821870, 
(float)0.046656439773674244, 
(float)-1.064746522092762104, 
(float)0.039859973663650149, 
(float)0.916864056141751926, 
(float)-0.408757914442315740, 
(float)0.401076600142600159, 
(float)0.634977399224949113, 
(float)3.330584999445134642, 
(float)-0.718457860992336883, 
(float)-0.203966705428681339, 
(float)-0.429912322646474054, 
(float)-1.532969594418329251, 
(float)0.183697860562045207, 
(float)0.325417835540126932, 
(float)-0.362456381681590778, 
(float)-0.044953045649371547, 
(float)-0.102380214332169081, 
(float)-0.302207476831308608, 
(float)-0.853594868896980552, 
(float)-0.719295939905001180, 
(float)-0.917032198799090037, 
(float)0.698911919071929510, 
(float)-0.025877560840669049, 
(float)0.328050343183217019, 
(float)-0.701057374769319397};
#ifdef SOC_C6678
#pragma DATA_SECTION(DTF_gf_test_output_data, ".gsvd_unit_test");
#pragma DATA_ALIGN(DTF_gf_test_output_data, 2);
#endif // SOC_C6678
const float DTF_gf_test_output_data[320] = {(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.021751019258550996, 
(float)-0.024736311085757082, 
(float)-0.000541290210541880, 
(float)-0.009964452521456167, 
(float)0.015521399884489522, 
(float)-0.010538681137529919, 
(float)0.013376438684499958, 
(float)-0.012719353959054110, 
(float)0.017929778701947542, 
(float)0.006204264433438475, 
(float)-0.019735234649536852, 
(float)-0.019156235517655704, 
(float)0.000942733420843449, 
(float)-0.032918169273833328, 
(float)0.015239621525309426, 
(float)0.024570831958599132, 
(float)0.011005972171672302, 
(float)-0.019095962740425937, 
(float)0.004002096256023917, 
(float)0.037239313920040998, 
(float)0.020929983123731188, 
(float)0.009083020487249053, 
(float)0.014546769413715945, 
(float)0.022356745776467842, 
(float)0.003196468408620294, 
(float)-0.001772612439783041, 
(float)-0.004489548932215461, 
(float)0.002688168183676962, 
(float)-0.003865508425823689, 
(float)-0.012716211493888286, 
(float)-0.015471127557393573, 
(float)0.010115962470548589};
#endif // DTF_GF_UNIT_TEST_H_