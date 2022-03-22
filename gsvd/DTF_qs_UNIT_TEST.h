#ifndef DTF_QS_UNIT_TEST_H_
#define DTF_QS_UNIT_TEST_H_

const int DTF_qs_test_nsamples = 10;
const int DTF_qs_test_vec_len = 32;
#ifdef SOC_C6678
#pragma DATA_SECTION(DTF_qs_test_input_data, ".gsvd_unit_test");
#pragma DATA_ALIGN(DTF_qs_test_input_data, 2);
#endif // SOC_C6678
const float DTF_qs_test_input_data[320] = {(float)0.330044188884254186, 
(float)-1.400141860139974437, 
(float)-0.521881084053462008, 
(float)1.004918393567769908, 
(float)-1.137789385757429050, 
(float)-0.153247997594284674, 
(float)-0.974249346209883793, 
(float)-0.979501189164529329, 
(float)-0.921452084469282839, 
(float)0.823138388315127423, 
(float)0.006565076507505641, 
(float)0.374132781703700679, 
(float)-0.555195218803247736, 
(float)-0.124638466028382147, 
(float)0.836974250432235611, 
(float)-1.287476203065973213, 
(float)-0.758512754220414198, 
(float)1.020577089709642449, 
(float)1.694427392443052849, 
(float)-0.863188280304949762, 
(float)0.439280577503744052, 
(float)-1.246878038575009118, 
(float)0.657701771773509747, 
(float)0.133127764680656291, 
(float)-1.013790064393899959, 
(float)0.508966617988000469, 
(float)1.264501024757881842, 
(float)-0.157605025675004590, 
(float)-0.898631249218897921, 
(float)-1.117966299047454815, 
(float)-1.241883403201153202, 
(float)0.398455300311777116, 
(float)0.339393132932247765, 
(float)-0.783577082725982477, 
(float)0.754028533121159250, 
(float)-1.065583717650424145, 
(float)1.487362837189412090, 
(float)-2.127732425694508933, 
(float)-0.273774444044906029, 
(float)0.753309636067282740, 
(float)0.012275059656205654, 
(float)0.049070103964110399, 
(float)-0.508520216450020768, 
(float)1.965257547665530513, 
(float)-0.460335120053997959, 
(float)0.697998178202231423, 
(float)1.211256587779186988, 
(float)-0.339759120818416582, 
(float)1.448645580327399207, 
(float)0.443910563663409752, 
(float)-1.487802376490370060, 
(float)-0.471275689197211134, 
(float)-0.145215110726913454, 
(float)0.637923187088797361, 
(float)0.712707186161947948, 
(float)0.697064159201886580, 
(float)-1.446998808382657931, 
(float)-1.525752055596325318, 
(float)1.345511654869109730, 
(float)0.823446603203802918, 
(float)0.412184548983950572, 
(float)1.546189754135908867, 
(float)1.846948717748590374, 
(float)-0.772296031100817237, 
(float)0.041902847055275763, 
(float)0.431067421693822062, 
(float)0.120365366497739934, 
(float)0.202805281480508554, 
(float)0.194154727168525776, 
(float)1.086571338691319832, 
(float)-2.748723640975913263, 
(float)-0.005891802541244979, 
(float)-0.250432973297585681, 
(float)-0.468704021498140500, 
(float)0.144009406187684180, 
(float)0.534210961282279850, 
(float)-0.284940424494448341, 
(float)0.018133548858779706, 
(float)-1.649917809343881547, 
(float)-1.114290940491807991, 
(float)-0.373310711431173392, 
(float)-0.170381047257563312, 
(float)-1.066977132405122708, 
(float)-1.180644345563165443, 
(float)0.612916814816418465, 
(float)0.134828653192903547, 
(float)1.376903270127391554, 
(float)0.545738785212606992, 
(float)-1.165635853734562799, 
(float)-2.218573279490055228, 
(float)0.139236703024912256, 
(float)-0.227141607142595375, 
(float)0.554559503688101807, 
(float)0.913972182976413028, 
(float)-0.200183410039571130, 
(float)0.148786991660663753, 
(float)-0.721357482590995303, 
(float)1.201293096852099840, 
(float)0.051885203915893727, 
(float)-0.532589246720482690, 
(float)-0.457453476485852828, 
(float)1.818272819445754473, 
(float)0.507958613771411716, 
(float)0.420440280924548104, 
(float)0.336928312392418772, 
(float)0.454330108190716397, 
(float)0.472254359747473151, 
(float)0.006376235234114317, 
(float)1.711590606750400978, 
(float)-0.239429046105734816, 
(float)-0.843438104440475289, 
(float)-0.412751293072427361, 
(float)1.182966073136458851, 
(float)0.781520642853550052, 
(float)1.171962011327632780, 
(float)-0.214152932826880499, 
(float)0.150936524702796449, 
(float)-1.814309792420289114, 
(float)0.945596698383371126, 
(float)-0.107487175860458820, 
(float)0.056038543573655231, 
(float)1.013494534161992311, 
(float)-0.273372627332765017, 
(float)0.430841310456162474, 
(float)-0.717847862328608088, 
(float)-0.531839351632113488, 
(float)0.541662508855142000, 
(float)-0.211772194693872123, 
(float)-1.565650523910892877, 
(float)-0.537865066093256017, 
(float)2.909509160426209551, 
(float)0.492827187127412913, 
(float)0.215098339176153674, 
(float)-0.409014743879361986, 
(float)-1.819450969211250380, 
(float)0.135598306814047470, 
(float)-3.078963217553082554, 
(float)-0.923381458365137631, 
(float)-1.455122468047093554, 
(float)-0.213293850410608360, 
(float)1.073617254254550790, 
(float)0.515949709248550215, 
(float)-0.443665953173888683, 
(float)-1.626537957617615549, 
(float)-0.533168110613641444, 
(float)-1.185578326171744079, 
(float)0.429481838840398034, 
(float)-0.585620614856441346, 
(float)1.416744069636067582, 
(float)-0.117376955207757636, 
(float)-1.518860186646197041, 
(float)0.079236130199065863, 
(float)0.717367667836473322, 
(float)-0.495938823515462091, 
(float)0.617738374578965743, 
(float)0.339304058429669764, 
(float)0.384447387876510671, 
(float)-0.326549398092084608, 
(float)-0.127644532625117241, 
(float)-0.134267390260558089, 
(float)-0.128478778727586451, 
(float)-1.455733850369439253, 
(float)-0.018265990348025965, 
(float)-1.190436819819526093, 
(float)0.127946580186515252, 
(float)-1.166445332585606343, 
(float)1.362765218005044465, 
(float)0.820975155773298049, 
(float)-0.539193124703502447, 
(float)2.064612632100626399, 
(float)1.139357118943751690, 
(float)0.853397161099404222, 
(float)-2.072750726940255195, 
(float)-1.265754005978191321, 
(float)-0.702280836137229914, 
(float)-0.327693685580523753, 
(float)-1.311551364351345672, 
(float)0.655080616885059142, 
(float)-0.522712044450634350, 
(float)-0.165371801417419334, 
(float)-0.548545699795531916, 
(float)-0.088259382819708618, 
(float)1.372179949780865549, 
(float)-1.830471440825206964, 
(float)-0.961464463422430526, 
(float)-0.470914614668696607, 
(float)0.554739930695867467, 
(float)-1.023085139475663041, 
(float)-0.524780785456312460, 
(float)0.703483761092186244, 
(float)-1.227934717755416738, 
(float)1.047608984621426931, 
(float)0.342178667824183269, 
(float)0.569912411035799926, 
(float)-0.014888968642419703, 
(float)-0.997451958416481599, 
(float)-1.599527645001668219, 
(float)0.153380701845757195, 
(float)0.715557352603360175, 
(float)0.724202711399354326, 
(float)-0.086045747729814659, 
(float)1.648136441246676576, 
(float)0.185027816292803932, 
(float)-0.402985410257423904, 
(float)0.105222786683522293, 
(float)-0.615970146656799500, 
(float)0.687530550436663668, 
(float)1.556752773716637561, 
(float)1.040086181945185206, 
(float)0.248261614820493998, 
(float)-1.360803627975466723, 
(float)-0.636671631102359248, 
(float)0.403044332731673005, 
(float)-0.076599974490967948, 
(float)1.382435835061783136, 
(float)0.660856078828915394, 
(float)-1.433693610850134359, 
(float)0.632975922545198522, 
(float)0.668609506858592662, 
(float)1.750700220071471858, 
(float)0.085325717003553112, 
(float)0.263015304476001410, 
(float)-1.575409126355190148, 
(float)-0.460339097298517685, 
(float)-1.493549210259366156, 
(float)-0.147965019754106780, 
(float)-0.779475521158073836, 
(float)-1.288077160676531108, 
(float)-0.004485191472661998, 
(float)-0.840699961301648591, 
(float)1.267781171141917351, 
(float)2.227383528358616527, 
(float)0.152662012471871278, 
(float)0.282260300167546108, 
(float)-1.958344948983796296, 
(float)1.497394054403624608, 
(float)-0.623825627076610933, 
(float)0.390898555416019422, 
(float)-0.201298040688494551, 
(float)0.343561984023575184, 
(float)-0.086392272838556536, 
(float)0.130692157622464472, 
(float)-1.064056660456754067, 
(float)0.132694805336031063, 
(float)-1.488370029016311102, 
(float)-0.108566549523560124, 
(float)0.182589623369831644, 
(float)-0.278445613171680095, 
(float)0.325719529769900207, 
(float)0.884995339799298786, 
(float)-1.593998521732101548, 
(float)-1.455360674012253108, 
(float)-0.619775689446780409, 
(float)0.428207743879076286, 
(float)0.345703163444325001, 
(float)-0.355340755001850861, 
(float)0.580104779822905314, 
(float)2.078772331111004235, 
(float)-1.079049362703566883, 
(float)-0.846084930547681413, 
(float)-1.829996145727891710, 
(float)0.133610744632336020, 
(float)0.794793543289386450, 
(float)-0.371500827123233568, 
(float)1.090049088205758743, 
(float)-0.231560754617726405, 
(float)0.243704350261722574, 
(float)1.013883429802165503, 
(float)0.587913046780830228, 
(float)0.315685111601659463, 
(float)1.426476732566162031, 
(float)-0.914058512648528665, 
(float)-0.464747795930260665, 
(float)0.296200815992260336, 
(float)-0.357042534394587663, 
(float)-0.563856672147710181, 
(float)0.720381994652540270, 
(float)-0.507635058061088107, 
(float)0.395061515612727676, 
(float)-0.183371271557390497, 
(float)-0.435802438576955720, 
(float)0.457254172915096180, 
(float)0.291098344535306697, 
(float)-1.973707065205020594, 
(float)-0.339056554606072813, 
(float)-1.078613093117751776, 
(float)0.111895664685945251, 
(float)-0.717465469357702168, 
(float)-0.014159069945206141, 
(float)1.253577956647451863, 
(float)1.701752828152111929, 
(float)0.798545863074570317, 
(float)-1.598119743787426383, 
(float)1.467198682292286671, 
(float)1.075071620874361811, 
(float)0.253438093812876297, 
(float)2.430472184859199025, 
(float)-0.460952059904311762, 
(float)1.793683151494429362, 
(float)-1.106499322451205636, 
(float)-0.397231989549590214, 
(float)-1.172554499896679037, 
(float)0.562614263538735004, 
(float)0.363942575526966239, 
(float)-0.651217860334075360, 
(float)-1.406971329523112546, 
(float)-2.697613584567738254, 
(float)-0.953621301959846179, 
(float)-1.434529278420271448, 
(float)0.661083447241107680, 
(float)1.077427719807635853, 
(float)-2.002162696442355116, 
(float)-1.747387720534013145, 
(float)-0.478948170222289138, 
(float)0.947337327600543344, 
(float)1.253198245915724263, 
(float)1.470473077269853102, 
(float)-0.396390494463063792, 
(float)-0.657613697601584057, 
(float)-1.033756244118256840};
#ifdef SOC_C6678
#pragma DATA_SECTION(DTF_qs_test_output_data, ".gsvd_unit_test");
#pragma DATA_ALIGN(DTF_qs_test_output_data, 2);
#endif // SOC_C6678
const float DTF_qs_test_output_data[320] = {(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000726696299, 
(float)-0.000000003082853574, 
(float)-0.000000001149085683, 
(float)0.000000002212644553, 
(float)-0.000000002505201918, 
(float)-0.000000000337423764, 
(float)-0.000000002145116980, 
(float)-0.000000002156680567, 
(float)-0.000000002028867169, 
(float)0.000000001812398582, 
(float)0.000000000014455085, 
(float)0.000000000823771231, 
(float)-0.000000001222437249, 
(float)-0.000000000274430864, 
(float)0.000000001842862593, 
(float)-0.000000002834784622, 
(float)-0.000000001670104881, 
(float)0.000000002247122108, 
(float)0.000000003730815920, 
(float)-0.000000001900581041, 
(float)0.000000000967214635, 
(float)-0.000000002745394968, 
(float)0.000000001448137732, 
(float)0.000000000293122730, 
(float)-0.000000002232178333, 
(float)0.000000001120650415, 
(float)0.000000002784197526, 
(float)-0.000000000347017135, 
(float)-0.000000001978619908, 
(float)-0.000000002461555145, 
(float)-0.000000002734397704, 
(float)0.000000000877324921, 
(float)0.000000002957970650, 
(float)-0.000000011103670007, 
(float)-0.000000001835413002, 
(float)0.000000004384888606, 
(float)-0.000000004346200482, 
(float)-0.000000005711353546, 
(float)-0.000000007128481439, 
(float)-0.000000004902209840, 
(float)-0.000000006145008652, 
(float)0.000000005621558222, 
(float)-0.000000001075693570, 
(float)0.000000006833136138, 
(float)-0.000000004732360801, 
(float)0.000000000702014235, 
(float)0.000000008273152897, 
(float)-0.000000009371811978, 
(float)-0.000000001890992105, 
(float)0.000000007813400494, 
(float)0.000000008073684681, 
(float)-0.000000006819437576, 
(float)0.000000002622635986, 
(float)-0.000000006947203136, 
(float)0.000000005974643021, 
(float)0.000000002426517873, 
(float)-0.000000009976554798, 
(float)0.000000000049717255, 
(float)0.000000011432401670, 
(float)0.000000000757413096, 
(float)-0.000000005111624206, 
(float)-0.000000004083896223, 
(float)-0.000000004251697513, 
(float)0.000000000968465356, 
(float)0.000000006106336701, 
(float)-0.000000020168786701, 
(float)-0.000000000599440186, 
(float)0.000000004698962799, 
(float)-0.000000002505762202, 
(float)-0.000000013596401724, 
(float)-0.000000018928236452, 
(float)-0.000000006068976436, 
(float)-0.000000010913044988, 
(float)0.000000008626237876, 
(float)-0.000000003014659663, 
(float)0.000000018580318559, 
(float)-0.000000010003440807, 
(float)0.000000003302563502, 
(float)0.000000013966755178, 
(float)-0.000000019321647947, 
(float)0.000000000284220159, 
(float)0.000000014165591615, 
(float)0.000000006890032328, 
(float)-0.000000015539730559, 
(float)0.000000005355718496, 
(float)-0.000000009562497339, 
(float)0.000000015259992990, 
(float)0.000000007379552608, 
(float)-0.000000023749177205, 
(float)-0.000000009335929832, 
(float)0.000000023651049274, 
(float)0.000000003229139626, 
(float)-0.000000006203287162, 
(float)-0.000000000302147497, 
(float)-0.000000002145272309, 
(float)-0.000000000329218693, 
(float)0.000000007856259292, 
(float)-0.000000025905680687, 
(float)0.000000001058992601, 
(float)0.000000004297971819, 
(float)-0.000000001179070627, 
(float)-0.000000015303357323, 
(float)-0.000000036091547959, 
(float)-0.000000006355817446, 
(float)-0.000000015641457969, 
(float)0.000000011678183326, 
(float)-0.000000003653452996, 
(float)0.000000031894200456, 
(float)-0.000000012301908582, 
(float)0.000000005497504955, 
(float)0.000000014304050511, 
(float)-0.000000032965185990, 
(float)0.000000004303340937, 
(float)0.000000022052809838, 
(float)0.000000005868680978, 
(float)-0.000000027627516025, 
(float)0.000000009868867114, 
(float)-0.000000015949119172, 
(float)0.000000029978532345, 
(float)0.000000013464143321, 
(float)-0.000000040417309170, 
(float)-0.000000021722234385, 
(float)0.000000035952586226, 
(float)0.000000006221166522, 
(float)-0.000000007671629439, 
(float)0.000000004464710520, 
(float)0.000000000778049993, 
(float)-0.000000001803697731, 
(float)0.000000004603767038, 
(float)-0.000000030317730391, 
(float)0.000000009291690851, 
(float)0.000000003780572937, 
(float)-0.000000000353060916, 
(float)-0.000000013907319928, 
(float)-0.000000056655050316, 
(float)-0.000000005412649804, 
(float)-0.000000026539305902, 
(float)0.000000013797044112, 
(float)-0.000000006462887795, 
(float)0.000000045156246600, 
(float)-0.000000008491870978, 
(float)0.000000008362003225, 
(float)0.000000011786867915, 
(float)-0.000000051521998362, 
(float)0.000000009907067740, 
(float)0.000000029305298075, 
(float)0.000000008363313335, 
(float)-0.000000041848850562, 
(float)0.000000017974912491, 
(float)-0.000000026824705163, 
(float)0.000000043907563708, 
(float)0.000000019669366128, 
(float)-0.000000055886169913, 
(float)-0.000000033327098647, 
(float)0.000000049373644275, 
(float)0.000000011010476341, 
(float)-0.000000009932098871, 
(float)0.000000007479150703, 
(float)0.000000004719262065, 
(float)-0.000000004091133385, 
(float)-0.000000002524219832, 
(float)-0.000000039249987722, 
(float)0.000000024216645818, 
(float)0.000000001719118420, 
(float)0.000000001260093537, 
(float)-0.000000015933575860, 
(float)-0.000000078884357409, 
(float)-0.000000002325438390, 
(float)-0.000000045806142795, 
(float)0.000000018464342342, 
(float)-0.000000010087147489, 
(float)0.000000060214020989, 
(float)-0.000000006726856034, 
(float)0.000000009673312124, 
(float)0.000000006645585920, 
(float)-0.000000074976932482, 
(float)0.000000011609213623, 
(float)0.000000035572310307, 
(float)0.000000010736728271, 
(float)-0.000000058162470438, 
(float)0.000000028272810175, 
(float)-0.000000038485122253, 
(float)0.000000057891841210, 
(float)0.000000022204820246, 
(float)-0.000000072329568412, 
(float)-0.000000047419693949, 
(float)0.000000065783988731, 
(float)0.000000014447772397, 
(float)-0.000000012557564913, 
(float)0.000000011406876348, 
(float)0.000000005795903993, 
(float)-0.000000004441145132, 
(float)-0.000000009412376277, 
(float)-0.000000050423899039, 
(float)0.000000039529935247, 
(float)-0.000000005255257542, 
(float)-0.000000000313063176, 
(float)-0.000000020270698192, 
(float)-0.000000097159316895, 
(float)0.000000004284437110, 
(float)-0.000000067047099142, 
(float)0.000000031490808436, 
(float)-0.000000010877448441, 
(float)0.000000076721024845, 
(float)-0.000000009280601397, 
(float)0.000000006846243745, 
(float)0.000000001284628453, 
(float)-0.000000096429886477, 
(float)0.000000012728263335, 
(float)0.000000044017503619, 
(float)0.000000009018946657, 
(float)-0.000000076725523109, 
(float)0.000000038546924288, 
(float)-0.000000050855913171, 
(float)0.000000078378105475, 
(float)0.000000022186027259, 
(float)-0.000000094541777826, 
(float)-0.000000061582863350, 
(float)0.000000085377785404, 
(float)0.000000019562366665, 
(float)-0.000000016237724188, 
(float)0.000000017596489762, 
(float)0.000000000701111886, 
(float)-0.000000003481162543, 
(float)-0.000000019041780749, 
(float)-0.000000060976189857, 
(float)0.000000053555666525, 
(float)-0.000000017505786751, 
(float)-0.000000005506206027, 
(float)-0.000000026241773097, 
(float)-0.000000111562579090, 
(float)0.000000017619520533, 
(float)-0.000000088774898350, 
(float)0.000000049201615575, 
(float)-0.000000015584726596, 
(float)0.000000096099760195, 
(float)-0.000000013049219608, 
(float)0.000000003412580660, 
(float)-0.000000003162782287, 
(float)-0.000000114277310924, 
(float)0.000000015997396764, 
(float)0.000000053540624781, 
(float)0.000000001867868130, 
(float)-0.000000096950857828, 
(float)0.000000046741346116, 
(float)-0.000000063994742084, 
(float)0.000000102941154925, 
(float)0.000000023006631884, 
(float)-0.000000119868679797, 
(float)-0.000000072796470514, 
(float)0.000000103514101320, 
(float)0.000000025517664797, 
(float)-0.000000021198621061, 
(float)0.000000025499606341, 
(float)-0.000000007303329218, 
(float)-0.000000004294175560, 
(float)-0.000000031012222179, 
(float)-0.000000067573415396, 
(float)0.000000063880141898, 
(float)-0.000000034866186296, 
(float)-0.000000014901913498, 
(float)-0.000000033961754987, 
(float)-0.000000121771337089, 
(float)0.000000035508590004, 
(float)-0.000000108393038837, 
(float)0.000000067562916606, 
(float)-0.000000024252815154, 
(float)0.000000121592321437, 
(float)-0.000000017023238998, 
(float)0.000000001430708713, 
(float)-0.000000005057197953, 
(float)-0.000000133858215316, 
(float)0.000000018143756962, 
(float)0.000000064272066266, 
(float)-0.000000008668746763, 
(float)-0.000000118698159315, 
(float)0.000000053437061596, 
(float)-0.000000078866087680, 
(float)0.000000129491242603, 
(float)0.000000022812605671, 
(float)-0.000000146152824084, 
(float)-0.000000081337931717, 
(float)0.000000119247859793, 
(float)0.000000024060503479, 
(float)-0.000000028428686428, 
(float)0.000000032215092331, 
(float)-0.000000014544427926, 
(float)-0.000000007500516115};
#endif // DTF_QS_UNIT_TEST_H_