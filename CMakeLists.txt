
set(bandlimited_sawtooth_synthesis_sources
    sample/BLITSaw_processor.h
    sample/BLITSaw_controller.cpp
    sample/BLITSaw_controller.h
    sample/BLITSaw_entry.cpp
    sample/BLITSaw_guids.h
    sample/BLITSaw_oscillator.cpp
    sample/BLITSaw_oscillator.h
    sample/BLITSaw_processor.cpp
)

set(target bandlimited_sawtooth_synthesis)
smtg_add_vst3plugin(${target} ${bandlimited_sawtooth_synthesis_sources})
set_target_properties(${target} PROPERTIES ${SDK_IDE_PLUGIN_EXAMPLES_FOLDER})
target_link_libraries(${target} PRIVATE sdk)
