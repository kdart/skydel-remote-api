import utility

GNSS_ID = {0: "GPS", 2: "GALILEO"}
SIGNAL_MASK = {0:["L1C/A", "Reserved", "Reserved", "L1C(D)", "L1C(P)", "L1C(D+P)", "L2 CM", "L2 CL", "L2 CM+CL", "L2 P", "Reserved", "L5 I", "L5 Q", "L5 I + L5 Q", "Reserved", "Reserved"],
               2:["E1-B I/NAV OS","E1-C","E1-B + E1-C","E5a-I F/NAV OS","E5a-Q","E5a-I+E5a-Q","E5b-I I/NAV OS","E5b-Q","E5b-I+E5b-Q","E5-I","E5-Q","E5-I + E5-Q", "E6-B C/NAV HAS", "E6-C", "E6-B + E6-C" , "Reserved"]
              }

def phaseBlock(msg, sys):
    gnssID = int(msg[f'gnss_id {sys}']['decimal'])
    satellite_mask = msg[f'satellite_mask {sys}']['binary']
    signal_mask = msg[f'signal_mask {sys}']['binary']

    phase_biases_per_sat = []
    svID = 1
    for sat in range(len(satellite_mask)):
        if (int(satellite_mask[sat]) == 1):
            phase_bias_per_sig = []
            signal = 1
            signalCount = 1
            for sig in range(len(signal_mask)):
                if (int(signal_mask[sig]) == 1):
                    phase_bias_per_sig.append({
                        'sig': SIGNAL_MASK[gnssID][signal - 1], 
                        'phase_bias': msg[f'pb sys{sys} sat{svID} sig{signalCount}']['decimal'],
                        'discontinuity_indicator': msg[f'pbi sys{sys} sat{svID} sig{signalCount}']['decimal'],
                        })
                    signalCount = signalCount + 1
                signal = signal + 1 

            phase_biases_per_sat.append({ 
                'sat': svID,
                'phase_bias_per_sig': phase_bias_per_sig
             })
        svID = svID + 1

    return {'gnss_id': GNSS_ID[gnssID],
            'phase_biases_per_sat': phase_biases_per_sat
            } 

def phase(msg):
    vi = int(msg['phase_validity_interval_index']['decimal'])

    phase_biases_per_sys = []
    for sys in range(1, int(msg['n_sys']['decimal']) + 1):
        phase_biases_per_sys.append(phaseBlock(msg, sys))

    return {'phase_biases' : 
        {'validity_interval_index' : vi,
            'phase_biases_per_sys': phase_biases_per_sys
        }}

def handlePhaseBlock(gen, nsys, satCounts, sigCounts):
    gen.addParametertoDict('phase_validity_interval_index', 4)
    for sys in range(1, nsys + 1):
        for sat in range(1, satCounts[sys - 1] + 1):
            for sig in range(1, sigCounts[sys - 1] + 1):
                gen.addParametertoDict("pb sys{0} sat{1} sig{2}".format(sys, sat, sig), 11, True, 0.01, utility.METER)
                gen.addParametertoDict("pbi sys{0} sat{1} sig{2}".format(sys, sat, sig), 2)
