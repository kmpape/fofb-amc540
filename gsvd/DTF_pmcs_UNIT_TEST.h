#ifndef DTF_PMCS_UNIT_TEST_H_
#define DTF_PMCS_UNIT_TEST_H_

const int DTF_pmcs_test_nsamples = 10;
const int DTF_pmcs_test_vec_len = 32;
#ifdef SOC_C6678
#pragma DATA_SECTION(DTF_pmcs_test_input_data, ".gsvd_unit_test");
#pragma DATA_ALIGN(DTF_pmcs_test_input_data, 2);
#endif // SOC_C6678
const float DTF_pmcs_test_input_data[320] = {(float)-2.166338522817710111, 
(float)0.049773258078723688, 
(float)0.626116179073086698, 
(float)1.143575242198606512, 
(float)-1.821657007606681145, 
(float)0.296885028427864628, 
(float)0.158513910062322461, 
(float)0.046149690443509084, 
(float)-0.110605642711331956, 
(float)1.944653611450073871, 
(float)-1.157974975240329440, 
(float)0.201390599305947049, 
(float)0.441787611444532102, 
(float)-1.976718734249298892, 
(float)0.438806572220904634, 
(float)1.458027580832865988, 
(float)-0.286834147687734964, 
(float)-0.291272040152445899, 
(float)-1.456210718055861220, 
(float)0.303052562331900643, 
(float)1.036554246715127414, 
(float)-1.257417687088367986, 
(float)-1.351432564173413953, 
(float)-0.600420001596877140, 
(float)0.096061130248928067, 
(float)1.120742164221635750, 
(float)0.562056733354769356, 
(float)-0.082256189629015916, 
(float)-0.843578031481675761, 
(float)0.060899106700450227, 
(float)0.538866867694518525, 
(float)-0.721784691404919077, 
(float)0.230002173722855557, 
(float)0.270126734198968710, 
(float)1.326600776985154884, 
(float)1.556130662209000981, 
(float)-1.863233098302702562, 
(float)1.094457428001466059, 
(float)-0.649484120815920440, 
(float)-1.312394200976678915, 
(float)-0.606382667338401071, 
(float)-0.477353467466016423, 
(float)0.312420307934394015, 
(float)-0.215758550505995267, 
(float)-1.352116974258823934, 
(float)-0.348265371537667456, 
(float)-1.907294168930572242, 
(float)1.582316014877399812, 
(float)-0.643684362337669014, 
(float)0.695392761549660787, 
(float)0.667289163294482068, 
(float)-0.654413203987752601, 
(float)-1.527240530711819311, 
(float)-1.531567882312290241, 
(float)0.807009714742315198, 
(float)-0.119675243824766644, 
(float)1.062896350941788359, 
(float)-0.467908729443710703, 
(float)-2.927289789791459818, 
(float)-1.085131005818850136, 
(float)0.795715184956298227, 
(float)0.207817784033833691, 
(float)1.870702363648561128, 
(float)0.346524811477271710, 
(float)-1.793111833506796593, 
(float)2.482677041332422174, 
(float)1.072953485138292917, 
(float)-1.459947615670718735, 
(float)0.220999235306068104, 
(float)-0.044516544708873680, 
(float)-0.757763901073561841, 
(float)-1.813650765777050422, 
(float)-0.946917879354600034, 
(float)0.274561582954601535, 
(float)-0.555907242817070824, 
(float)-0.857137546258483485, 
(float)0.049140474991200236, 
(float)2.605765274277167087, 
(float)0.245635087607474545, 
(float)0.769333392684599437, 
(float)-0.541381747593522644, 
(float)-1.557411361723962218, 
(float)-1.127086223975299895, 
(float)0.542286995238034031, 
(float)0.048173884277367289, 
(float)-0.047135156129835772, 
(float)0.860924914655297746, 
(float)2.081143384253408168, 
(float)0.962929642658448159, 
(float)-0.334799876153928089, 
(float)0.301131513767468162, 
(float)0.941124835512759939, 
(float)0.070397969600040952, 
(float)1.473418986056943547, 
(float)1.236020366124566339, 
(float)0.599164670357369977, 
(float)-1.556386916993980574, 
(float)-1.196070309428255651, 
(float)-1.008940227543177359, 
(float)1.047621940189704004, 
(float)-0.025925692299105928, 
(float)1.901116309242278257, 
(float)-0.120378484439199282, 
(float)-0.010539007195499472, 
(float)-0.224091536315098983, 
(float)1.283920555954663145, 
(float)1.053820920177052312, 
(float)0.186586766332063309, 
(float)-0.500260714863253075, 
(float)-0.375385305691725013, 
(float)-0.363024984071078305, 
(float)0.681226605325267687, 
(float)1.013898793181218672, 
(float)1.645030806397379308, 
(float)1.038247221435796286, 
(float)-1.077942910431688661, 
(float)1.006039465324712445, 
(float)0.126451469584363402, 
(float)-0.709174692765666803, 
(float)-0.200848252362035795, 
(float)-0.144338146263979866, 
(float)0.001962907318414610, 
(float)0.141720330687094498, 
(float)-0.135503682895920102, 
(float)-0.444649758632709780, 
(float)1.232503108527909452, 
(float)1.447070093209266606, 
(float)0.545106281328291642, 
(float)0.069840673590714872, 
(float)1.422170057479551497, 
(float)-0.368797223303773514, 
(float)-0.301366363600470810, 
(float)0.056775356075792031, 
(float)0.996105220215060427, 
(float)-0.101873208791197295, 
(float)0.549226152660311828, 
(float)-0.100126677922052709, 
(float)0.223005932620624042, 
(float)-1.978037612815106927, 
(float)1.396710912429086848, 
(float)1.006556084410175744, 
(float)-1.060200466939379860, 
(float)-2.474853761973249355, 
(float)1.656834978064809949, 
(float)0.059075275499662031, 
(float)0.933868709569781852, 
(float)0.592923874710955978, 
(float)0.413650087339139827, 
(float)1.173636591568232079, 
(float)0.475997361645692896, 
(float)-1.704972880596346219, 
(float)0.679670567451280405, 
(float)-0.340339864806258219, 
(float)0.193926272546492057, 
(float)0.219588204598458597, 
(float)0.343217151082968186, 
(float)-0.557705597024540700, 
(float)-0.571439067199050688, 
(float)-1.074183768200875688, 
(float)1.097033924658028514, 
(float)0.093930288827672917, 
(float)0.453216961600440005, 
(float)1.034832754916127584, 
(float)-1.156033006447366729, 
(float)-1.134768910472938597, 
(float)-0.176269563047515648, 
(float)0.690617470849694048, 
(float)-0.868925241299088769, 
(float)-0.751541268801572460, 
(float)0.534177845891724123, 
(float)0.314294295296510040, 
(float)0.557116718558999025, 
(float)0.692532820404488270, 
(float)1.044525259277242046, 
(float)-1.736739704502263892, 
(float)0.144679679662558042, 
(float)0.368282713367655279, 
(float)-1.701395840778294311, 
(float)0.093210165315987109, 
(float)1.067441348756061670, 
(float)-1.520813357884190697, 
(float)0.042261200541627450, 
(float)-0.576056837527147536, 
(float)0.706954768968764635, 
(float)-1.122306284885204120, 
(float)-1.130536800225882210, 
(float)1.294699338757324014, 
(float)0.482227656023815843, 
(float)1.369992591937511994, 
(float)0.867083034987368717, 
(float)0.615412120537649598, 
(float)0.120114379793963041, 
(float)-1.321763978293132302, 
(float)-0.006808902205263216, 
(float)0.206221374721692829, 
(float)0.506637850954345437, 
(float)-0.912396946750922533, 
(float)0.091319998041778816, 
(float)1.718153599741542248, 
(float)-0.551423808180243169, 
(float)0.106105770126028218, 
(float)0.177598504733236573, 
(float)-0.917528103905870029, 
(float)0.362128477619500899, 
(float)0.211588599374471109, 
(float)-2.377087216894366417, 
(float)2.215803229155933529, 
(float)1.375268287571513204, 
(float)1.210863129515242553, 
(float)0.857555337297066678, 
(float)-0.342273105072761430, 
(float)-1.199149221251126773, 
(float)-0.469806287357720731, 
(float)0.502558934688587255, 
(float)1.910677916846739155, 
(float)-1.002049306968583409, 
(float)1.867604108284914632, 
(float)-1.052298918672311512, 
(float)0.803648744876789278, 
(float)-0.072667639302637782, 
(float)-1.952007038758227564, 
(float)2.499656153835267514, 
(float)-1.206560645344020299, 
(float)-0.707415721581517776, 
(float)-0.450934601369667343, 
(float)-0.375419479916476895, 
(float)0.212870257301937343, 
(float)0.329275472620116250, 
(float)2.092066848445502725, 
(float)1.421775007784571221, 
(float)0.963223484490905779, 
(float)-0.657400959298603094, 
(float)1.074259311977381559, 
(float)-0.198872652592877952, 
(float)-0.288717418855426122, 
(float)0.545881173531956754, 
(float)-1.195353544455447947, 
(float)-2.405089655022249140, 
(float)-0.413546207130279231, 
(float)-0.843357464571298232, 
(float)0.853352056739576814, 
(float)-0.262549095516801001, 
(float)1.439598477444735014, 
(float)-0.524780502631647106, 
(float)0.626301458468585426, 
(float)0.490373835570197592, 
(float)0.392133592055517233, 
(float)-0.969285165519699121, 
(float)0.060151653945149486, 
(float)-0.126577861081220239, 
(float)-0.577164018504162879, 
(float)-0.305176216049229898, 
(float)-0.483277869423016426, 
(float)-0.310288002415664343, 
(float)-0.861545467353032723, 
(float)-1.220023211748267888, 
(float)-0.645496405548498631, 
(float)-0.289142372427595273, 
(float)1.000421837876476427, 
(float)-0.588063687899176957, 
(float)1.557483431789156825, 
(float)-1.361373206035625172, 
(float)1.900081615117164002, 
(float)0.177859224675163963, 
(float)-2.166609613443961191, 
(float)0.706892217352585783, 
(float)-2.225334465521107141, 
(float)0.341199173780125542, 
(float)2.251238079111459456, 
(float)-0.166136696753434232, 
(float)0.487022958413381557, 
(float)0.672969018004066610, 
(float)-0.374955589348856644, 
(float)0.820488788272215497, 
(float)-0.374873842031478111, 
(float)0.878491832225579694, 
(float)-0.998011564904705994, 
(float)0.070460659378240476, 
(float)-0.290541681228906112, 
(float)-0.778342306603928336, 
(float)0.088556252710170522, 
(float)-1.473674430523000289, 
(float)-1.639794641552228649, 
(float)-1.453280703342443747, 
(float)-0.803375212344885403, 
(float)0.842577499099225080, 
(float)0.049842139061510408, 
(float)1.247959851060147729, 
(float)0.987095587387671114, 
(float)-0.481116512376636274, 
(float)-1.360795221745814798, 
(float)0.027717344037722871, 
(float)-0.347808476050095239, 
(float)1.224125256819629470, 
(float)-0.733649357582893402, 
(float)1.579551681041170053, 
(float)0.254257508977067115, 
(float)0.464392209794852462, 
(float)-0.715034025267173190, 
(float)-1.015842677160165852, 
(float)-0.176028006183455016, 
(float)0.021294551702541589, 
(float)-1.460903523125953063, 
(float)0.110445631979111156, 
(float)-0.768655824289017131, 
(float)0.421351093337351934, 
(float)0.976261997745148213, 
(float)-1.890918158476341038, 
(float)-0.725623229013660165, 
(float)-0.271065758149190150, 
(float)-2.251572482167134126, 
(float)-2.594147080265383654, 
(float)-1.693525952236357934, 
(float)0.895400435245059523, 
(float)1.618608185988281489, 
(float)-0.637890533983031638, 
(float)-0.451554193790718539, 
(float)0.177729373202334645, 
(float)0.814469569087516332, 
(float)0.879837752535385209};
#ifdef SOC_C6678
#pragma DATA_SECTION(DTF_pmcs_test_output_data, ".gsvd_unit_test");
#pragma DATA_ALIGN(DTF_pmcs_test_output_data, 2);
#endif // SOC_C6678
const float DTF_pmcs_test_output_data[320] = {(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)0.000000000000000000, 
(float)-0.002111680523681505, 
(float)0.000048517449409664, 
(float)0.000610318898447514, 
(float)0.001114722164093815, 
(float)-0.001775695526471811, 
(float)0.000289394443989447, 
(float)0.000154514510583429, 
(float)0.000044985306523901, 
(float)-0.000107814997085037, 
(float)0.001895588853428504, 
(float)-0.001128758583374616, 
(float)0.000196309395658889, 
(float)0.000430641049339680, 
(float)-0.001926844954260108, 
(float)0.000427735223494568, 
(float)0.001421240684687904, 
(float)-0.000279597152900716, 
(float)-0.000283923074720051, 
(float)-0.001419469662430767, 
(float)0.000295406367374052, 
(float)0.001010401371472022, 
(float)-0.001225692296928508, 
(float)-0.001317335123193066, 
(float)-0.000585271050690554, 
(float)0.000093637451253764, 
(float)0.001092465178146413, 
(float)0.000547875710341688, 
(float)-0.000080180817431026, 
(float)-0.000822294060010737, 
(float)0.000059362586306076, 
(float)0.000525270938674770, 
(float)-0.000703573637765886, 
(float)-0.002569628749918979, 
(float)0.000327501574580682, 
(float)0.002100603291393305, 
(float)0.002991685318021474, 
(float)-0.004165530456072617, 
(float)0.001449722680587333, 
(float)-0.000428669104446055, 
(float)-0.001219764573317227, 
(float)-0.000733726319722599, 
(float)0.002042621371785384, 
(float)-0.001188849669271121, 
(float)0.000049409421295456, 
(float)-0.000748248963880702, 
(float)-0.002888762284458799, 
(float)-0.001293263220470332, 
(float)0.003422744815536108, 
(float)-0.000997360723580416, 
(float)0.000302207347189217, 
(float)-0.001227555378416872, 
(float)-0.000247068926731040, 
(float)-0.000151910689503962, 
(float)-0.003114559672329917, 
(float)-0.000956232460195142, 
(float)-0.000890990015284714, 
(float)0.001159964500411996, 
(float)0.000989266856828186, 
(float)-0.002128573647323662, 
(float)-0.001163834560528775, 
(float)-0.000312285230651516, 
(float)0.000281113214723647, 
(float)0.002518455422710486, 
(float)-0.000593070958875655, 
(float)-0.004901169931046412, 
(float)0.002847672314074538, 
(float)0.003753836929122635, 
(float)0.002404917006942636, 
(float)-0.005088516124738702, 
(float)0.001840871705957988, 
(float)-0.001323819580485644, 
(float)-0.003386932146223793, 
(float)-0.001881191553162980, 
(float)0.002748899790349335, 
(float)-0.001983057593145062, 
(float)-0.000793048221801974, 
(float)-0.000992310267451626, 
(float)-0.001057072311932784, 
(float)-0.001521507341226288, 
(float)0.005112491489068708, 
(float)-0.001814639847361240, 
(float)-0.001085155240366858, 
(float)-0.002557111592586065, 
(float)0.000167253160929635, 
(float)-0.000271927611983179, 
(float)-0.004023593290661313, 
(float)-0.000272207343586717, 
(float)0.000918118443667682, 
(float)0.002462381846238461, 
(float)0.000855003483408482, 
(float)-0.002586575373950510, 
(float)-0.000613058254727294, 
(float)-0.000248589826400132, 
(float)0.001801239488953425, 
(float)0.004475546819005452, 
(float)-0.000118507026758399, 
(float)-0.007544023509579086, 
(float)0.002559839781556863, 
(float)0.003692287843845402, 
(float)0.003770652424920853, 
(float)-0.006138904196412549, 
(float)0.004097913849314048, 
(float)-0.001830317027888905, 
(float)-0.004352329389301017, 
(float)-0.002613652526391213, 
(float)0.004508532738694117, 
(float)-0.001373418587320973, 
(float)-0.000887774617455742, 
(float)-0.001745341489245543, 
(float)-0.001283503769375024, 
(float)-0.002247900503380879, 
(float)0.006922531976443973, 
(float)-0.001275257849972015, 
(float)0.000153761750372885, 
(float)-0.002121870671311861, 
(float)-0.000822690100711178, 
(float)0.000563171733041990, 
(float)-0.004745143765228473, 
(float)-0.000841481436392744, 
(float)0.001166590250440145, 
(float)0.002974775010797408, 
(float)0.000936107956402941, 
(float)-0.003076511408604800, 
(float)-0.000801389050577994, 
(float)-0.000664487511007019, 
(float)0.003547274581585387, 
(float)0.006998770503042429, 
(float)0.000496300952235257, 
(float)-0.009048271805397108, 
(float)0.004413983150264954, 
(float)0.003901504208026852, 
(float)0.004137686984852985, 
(float)-0.007077018000386329, 
(float)0.006055778989135481, 
(float)-0.002341777043851233, 
(float)-0.004738774250494477, 
(float)-0.003276106085950219, 
(float)0.005618487404868023, 
(float)-0.003371119212550379, 
(float)0.000266386228426606, 
(float)-0.001176902565267049, 
(float)-0.002300479698285868, 
(float)-0.005132794033497316, 
(float)0.009853756339474516, 
(float)-0.001330052332106993, 
(float)0.001231364862001207, 
(float)-0.001771488623119333, 
(float)-0.000700416891710450, 
(float)0.001883922654121524, 
(float)-0.005053390598332019, 
(float)-0.002609169102411945, 
(float)0.002193314426409418, 
(float)0.003225564389111540, 
(float)0.001201711987504619, 
(float)-0.003421705585416121, 
(float)-0.000563443256641389, 
(float)-0.001331165374347666, 
(float)0.003902137800057412, 
(float)0.007477156881464352, 
(float)0.001817701848241387, 
(float)-0.010446056755386592, 
(float)0.005753182089963452, 
(float)0.005340409258292707, 
(float)0.003550880254347607, 
(float)-0.009119717577132825, 
(float)0.007146450201184158, 
(float)-0.002096884039794814, 
(float)-0.006298914761640922, 
(float)-0.004583190559586035, 
(float)0.007067282275140208, 
(float)-0.003754115460315495, 
(float)0.001049943456127224, 
(float)-0.000581687810366271, 
(float)-0.001599835230954076, 
(float)-0.008059170029219277, 
(float)0.011781422637299111, 
(float)-0.001060221418632838, 
(float)0.000027992331063740, 
(float)-0.001712320081049172, 
(float)0.000200117342615930, 
(float)0.000941011499324273, 
(float)-0.005604226124169318, 
(float)-0.003809075559680759, 
(float)0.003446729109997678, 
(float)0.002584289320857352, 
(float)0.000234164599746577, 
(float)-0.002627938534237297, 
(float)-0.000078054249660484, 
(float)-0.000289596271480256, 
(float)0.005444209941000300, 
(float)0.009205205759501527, 
(float)0.002522744463725034, 
(float)-0.013135801156916965, 
(float)0.006751824754249116, 
(float)0.006280130913015530, 
(float)0.004199285359729596, 
(float)-0.011265741718221180, 
(float)0.008393484019710407, 
(float)-0.000616201020778296, 
(float)-0.007795051361958624, 
(float)-0.005268448765410722, 
(float)0.008300289589248392, 
(float)-0.005212125706964663, 
(float)0.001809842574154394, 
(float)-0.000233838818307074, 
(float)-0.003892979230785013, 
(float)-0.007632031800428167, 
(float)0.014884433916808475, 
(float)0.000150672985146945, 
(float)0.000765944579795069, 
(float)-0.002046499090158484, 
(float)-0.000767190730811426, 
(float)0.000523027976782450, 
(float)-0.005669328705493235, 
(float)-0.002741777376855475, 
(float)0.003235160009216376, 
(float)0.004486159742244060, 
(float)-0.001018519090464097, 
(float)-0.001886575013122356, 
(float)0.000017915052068086, 
(float)-0.002043449853812765, 
(float)0.008823468611591556, 
(float)0.009306549753187041, 
(float)0.002436503857117227, 
(float)-0.015337227615488579, 
(float)0.007349692368555569, 
(float)0.007261985237789429, 
(float)0.004827354508890019, 
(float)-0.010720576906330917, 
(float)0.010920682778855190, 
(float)0.000677558843408051, 
(float)-0.009530345098997929, 
(float)-0.004945696132817644, 
(float)0.009180439081157947, 
(float)-0.006323874754345439, 
(float)0.002847420054729899, 
(float)-0.001195857774568191, 
(float)-0.006962255747433077, 
(float)-0.009003056520350905, 
(float)0.016188316363160642, 
(float)0.001393596501531917, 
(float)0.000685709757639793, 
(float)-0.000750919609004985, 
(float)-0.001462288923454134, 
(float)0.001023748433805164, 
(float)-0.005565500672007262, 
(float)-0.002522223947731220, 
(float)0.002710395430076097, 
(float)0.005210334049059455, 
(float)-0.001691853016694612, 
(float)-0.002235647386506069, 
(float)-0.000141801701561383, 
(float)-0.002985712137402488, 
(float)0.010213894560269060, 
(float)0.009313644316629189, 
(float)0.001604562482966086, 
(float)-0.017800313709625353, 
(float)0.007875313602071929, 
(float)0.009047613179511520, 
(float)0.004652044166904992, 
(float)-0.009978353052136849, 
(float)0.011137354789102766, 
(float)0.003174893863878870, 
(float)-0.010615111117180226, 
(float)-0.007415046786346685, 
(float)0.010838113538906841, 
(float)-0.009381652890271510, 
(float)0.003837978673705897, 
(float)0.000817899810889297, 
(float)-0.008578132855134412, 
(float)-0.009587859651127396, 
(float)0.018620597624213153, 
(float)0.001692604094457819, 
(float)0.001571726497920081, 
(float)-0.000766009858505399, 
(float)-0.000947685354540509, 
(float)0.000142240876270926, 
(float)-0.005700705844872736, 
(float)-0.002837645529673244, 
(float)0.002049820557139479, 
(float)0.005954867293968923, 
(float)-0.003697389418922511, 
(float)-0.003809540573928555, 
(float)-0.001521868854291921, 
(float)-0.004373971952429669, 
(float)0.012564481284892466, 
(float)0.009903152436418731, 
(float)0.002780055599582983};
#endif // DTF_PMCS_UNIT_TEST_H_
