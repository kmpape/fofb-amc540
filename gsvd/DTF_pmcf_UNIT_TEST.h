#ifndef DTF_PMCF_UNIT_TEST_H_
#define DTF_PMCF_UNIT_TEST_H_

const int DTF_pmcf_test_nsamples = 10;
const int DTF_pmcf_test_vec_len = 16;
#ifdef SOC_C6678
#pragma DATA_SECTION(DTF_pmcf_test_input_data, ".gsvd_unit_test");
#pragma DATA_ALIGN(DTF_pmcf_test_input_data, 2);
#endif // SOC_C6678
const float DTF_pmcf_test_input_data[160] = {(float)2.505959557977604391, 
(float)0.472787993096300097, 
(float)-1.167981669548393997, 
(float)2.318648301728444494, 
(float)-0.997857136400435385, 
(float)-0.704987439045016040, 
(float)0.907164087520108020, 
(float)0.175537518078233229, 
(float)0.068244322806371258, 
(float)0.005916250737862531, 
(float)-1.339577330799121224, 
(float)-1.285450901252718658, 
(float)-1.676523018696671308, 
(float)0.755868016253086528, 
(float)-0.895768868332428525, 
(float)-1.734640794445276191, 
(float)0.476550199886526138, 
(float)-0.253969587070141611, 
(float)-1.303156833870763309, 
(float)0.290260392687051505, 
(float)0.439663451333156208, 
(float)0.503393235574352116, 
(float)-0.610059855304868170, 
(float)-0.353936356966121302, 
(float)-0.432099688896279921, 
(float)0.164478755253172321, 
(float)0.510496995046599955, 
(float)1.642761180090459794, 
(float)-0.615126067924009812, 
(float)-0.628671339470476265, 
(float)-0.176557908312170886, 
(float)1.161254133032621594, 
(float)-0.398468092854211975, 
(float)0.928355195202805183, 
(float)-0.735626270177556330, 
(float)-0.855994624611678079, 
(float)1.813110893905389265, 
(float)0.860349737621205035, 
(float)0.567824302200726549, 
(float)0.006641814849554211, 
(float)-0.599786854214077958, 
(float)1.175231150094827814, 
(float)1.131255858519449875, 
(float)-1.761915036584992045, 
(float)-1.151836040262490979, 
(float)-0.368293013835837069, 
(float)1.484138036814761641, 
(float)0.391096577027211900, 
(float)1.307652916450929848, 
(float)-0.577178565951492639, 
(float)0.477100296010847191, 
(float)-0.621523889494184245, 
(float)-1.875144016268395220, 
(float)0.307786196845485860, 
(float)0.039045499629782106, 
(float)-0.761705086537190934, 
(float)-0.549914774549614682, 
(float)-0.779440665402205912, 
(float)0.520463114879734401, 
(float)-1.040800861464549421, 
(float)0.591864830585221879, 
(float)-0.291608736237926547, 
(float)-0.236180217045200952, 
(float)-0.876779018252947684, 
(float)-0.836816341912152484, 
(float)-0.672945800076525935, 
(float)-0.919695072404639657, 
(float)-0.706421954056373314, 
(float)-0.642052446655979381, 
(float)-1.519737721379861517, 
(float)-1.745393863548854396, 
(float)-3.128906615334163810, 
(float)0.545687916708684773, 
(float)-0.974727752231522748, 
(float)0.221010185690586003, 
(float)-0.394221229858107480, 
(float)0.837841052967890132, 
(float)0.379404226606849526, 
(float)1.479598243338501540, 
(float)0.238174938734941305, 
(float)0.538982839646240497, 
(float)-0.378730385955060478, 
(float)-0.914676866000779465, 
(float)-1.724225267150852225, 
(float)-1.371254420478595693, 
(float)1.760743212446131745, 
(float)-1.298246173419001837, 
(float)0.512022254973961588, 
(float)0.068258041494724447, 
(float)0.689424323016320839, 
(float)-0.223780788972985506, 
(float)-0.273730017348495780, 
(float)0.630052649756426830, 
(float)-0.316732136825159383, 
(float)0.241652455586227555, 
(float)1.416869180274015205, 
(float)0.619090035834273245, 
(float)-0.594750146517122324, 
(float)-0.276208652567733470, 
(float)1.416600187594384996, 
(float)-1.784435178479461648, 
(float)0.318262013132834143, 
(float)1.546778140595395534, 
(float)0.011384618658942297, 
(float)0.198779155798662177, 
(float)0.966113999992253336, 
(float)2.307696925062159288, 
(float)0.955167978829482234, 
(float)-0.565779822388847831, 
(float)0.005643634158964442, 
(float)-0.685941575825115502, 
(float)0.010842069986046244, 
(float)-2.439050331628951795, 
(float)-1.006251642423469761, 
(float)0.559802846418436362, 
(float)0.478029105068941196, 
(float)-1.330897528607846825, 
(float)0.512117910447331015, 
(float)0.200783358582514032, 
(float)1.044970593119316282, 
(float)0.199954252281390327, 
(float)-0.942593527554870247, 
(float)-0.896738144289052741, 
(float)-1.237399305384043302, 
(float)0.238587252123928562, 
(float)0.845658854435910934, 
(float)-0.425389746723047857, 
(float)-0.323598062701874245, 
(float)-0.548663858017295336, 
(float)-2.200449471069738205, 
(float)-1.263137367482780382, 
(float)-0.416378216720860284, 
(float)0.326857590138703247, 
(float)-0.844070275018183214, 
(float)-1.214233420441408473, 
(float)-1.106181850556560375, 
(float)0.796695025372484822, 
(float)0.277352631564568630, 
(float)0.143552000426654641, 
(float)0.780401289153116795, 
(float)0.857441415847784660, 
(float)-0.625638087370598783, 
(float)-1.722887278776486841, 
(float)-1.457842254811369864, 
(float)0.900824520634748049, 
(float)0.470812866650540507, 
(float)-1.393605673987657889, 
(float)-0.414668993490136695, 
(float)-0.064050458771001212, 
(float)0.118022180317755951, 
(float)-0.061153603398749361, 
(float)-0.831023318540768163, 
(float)1.103528947235693058, 
(float)-0.499877176077259899, 
(float)-0.949443041955013722, 
(float)-1.961262405743634751, 
(float)-1.275655861540089919, 
(float)2.756551504580551537, 
(float)-0.597238258910734898, 
(float)1.483540421137801379};
#ifdef SOC_C6678
#pragma DATA_SECTION(DTF_pmcf_test_output_data, ".gsvd_unit_test");
#pragma DATA_ALIGN(DTF_pmcf_test_output_data, 2);
#endif // SOC_C6678
const float DTF_pmcf_test_output_data[160] = {(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.301093920536156023, 
(float)0.056806020660074140, 
(float)-0.140334339745890602, 
(float)0.278588257854940402, 
(float)-0.119893681594870322, 
(float)-0.084705050915552402, 
(float)0.108996807554814862, 
(float)0.021091034510555318, 
(float)0.008199633806017296, 
(float)0.000710844324628911, 
(float)-0.160951755628959414, 
(float)-0.154448402921263411, 
(float)-0.201436167220462065, 
(float)0.090818410734928010, 
(float)-0.107627658874954998, 
(float)-0.208419084760883500, 
(float)0.715521842488249349, 
(float)0.093676897542522203, 
(float)-0.463380438450368082, 
(float)0.643936111994152904, 
(float)-0.209290379367906232, 
(float)-0.124702355433498058, 
(float)0.164993865923574179, 
(float)0.003584218381148929, 
(float)-0.033990900873298029, 
(float)0.021316388254398820, 
(float)-0.290542480860662700, 
(float)-0.140281743442783047, 
(float)-0.514296054328130081, 
(float)0.123015323438476862, 
(float)-0.256513605549485102, 
(float)-0.316128270553387658, 
(float)0.796344892790704528, 
(float)0.180488652819184581, 
(float)-0.765830687100082175, 
(float)0.638692372577489564, 
(float)0.047020152809251356, 
(float)0.033319155702539141, 
(float)0.168269543917616032, 
(float)-0.041806314681898674, 
(float)-0.165987219807979675, 
(float)0.186108108090140056, 
(float)-0.114349656878382833, 
(float)-0.149014426951082357, 
(float)-0.781024379227804322, 
(float)0.007493350671088590, 
(float)-0.125082481930576972, 
(float)-0.145696766122061394, 
(float)0.785048994446299053, 
(float)0.214057967654182418, 
(float)-0.787549315232602409, 
(float)0.335082124365390033, 
(float)0.139850344449772623, 
(float)0.239785665789541969, 
(float)0.194505601490555680, 
(float)-0.149591805143711010, 
(float)-0.331380908751900072, 
(float)0.263659315734389943, 
(float)0.187646631802305452, 
(float)-0.422163638951332520, 
(float)-0.806591950786410106, 
(float)-0.132436827591902673, 
(float)0.097819828340247494, 
(float)-0.081872543935556291, 
(float)0.635836741071770239, 
(float)0.047835371378830205, 
(float)-0.689709595349467741, 
(float)-0.060269313532791635, 
(float)-0.101773136736920858, 
(float)0.153993728801729735, 
(float)-0.038991151391123524, 
(float)-0.630686338573620109, 
(float)-0.343001616562181255, 
(float)0.055394032819634301, 
(float)0.398683200643624003, 
(float)-0.637757598862511488, 
(float)-0.484154980456865724, 
(float)-0.167360194868118761, 
(float)0.358797113172184989, 
(float)-0.086019858880539493, 
(float)0.391345004706375343, 
(float)-0.171021918758906877, 
(float)-0.683382313953990739, 
(float)-0.552225435946654408, 
(float)-0.447289233263623687, 
(float)0.130624498288330365, 
(float)-0.494985125411407600, 
(float)-1.019611082248973899, 
(float)-0.211581677962054931, 
(float)-0.091102191827944490, 
(float)0.427621299938286237, 
(float)-0.693796668373191205, 
(float)-0.032765157051985461, 
(float)-0.150837953173006356, 
(float)0.606785863443611628, 
(float)0.124522989246030724, 
(float)0.292728491396043511, 
(float)-0.368625001762839799, 
(float)-0.653902450725630802, 
(float)-0.715780386660074153, 
(float)-0.899023258442046114, 
(float)0.302411854193253282, 
(float)-0.592277191389674051, 
(float)-0.966714961337089340, 
(float)-0.058709555134762115, 
(float)0.029508571184803885, 
(float)0.605157059448293233, 
(float)-0.486000138071138066, 
(float)0.229138101082620671, 
(float)-0.139084183640404202, 
(float)0.557749253609082785, 
(float)0.361021681965172425, 
(float)-0.059683585370364944, 
(float)-0.581533600993501598, 
(float)-0.453412100160852205, 
(float)-0.453655271513379810, 
(float)-1.299272928861819887, 
(float)0.428060978866464215, 
(float)-0.339499299326522008, 
(float)-0.596946400066456939, 
(float)0.086051901425478292, 
(float)0.075602934408072017, 
(float)0.696802246629244171, 
(float)-0.312851614280292345, 
(float)0.301673646730223566, 
(float)0.000443032034739735, 
(float)0.287275968357902811, 
(float)0.379929352386285168, 
(float)-0.558733433979087590, 
(float)-0.940974568603458850, 
(float)-0.334187997933856007, 
(float)-0.205326569953758531, 
(float)-1.337408126837708044, 
(float)0.355918483383925677, 
(float)-0.245192984648863743, 
(float)-0.281444413403322269, 
(float)0.266120664224164027, 
(float)0.024752484491460003, 
(float)0.524032427723774230, 
(float)-0.174115431769662099, 
(float)0.403900737699331103, 
(float)0.089878367878686180, 
(float)-0.181043045656809010, 
(float)0.099786245370731969};
#endif // DTF_PMCF_UNIT_TEST_H_
