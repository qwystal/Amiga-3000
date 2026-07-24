#ifndef ADDRESSING_MODES_H
#define ADDRESSING_MODES_H


byte *data_register_direct_mode(A3000 *a3000, AMA ama);
byte *address_register_direct_mode(A3000 *a3000, AMA ama);
byte *address_register_indirect_mode(A3000 *a3000, AMA ama);
byte *address_register_indirect_with_postincrement_mode(A3000 *a3000, AMA ama);
byte *address_register_indirect_with_predecrement_mode(A3000 *a3000, AMA ama);
byte *address_register_indirect_with_displacement_mode(A3000 *a3000, AMA ama);
byte *address_register_indirect_with_index_8bit_mode(A3000 *a3000, AMA ama);
byte *address_register_indirect_with_index_base_displacement_mode(A3000 *a3000, AMA ama);
byte *memory_indirect_postindexed_mode(A3000 *a3000, AMA ama);
byte *memory_indirect_preindexed_mode(A3000 *a3000, AMA ama);
byte *program_counter_indirect_with_displacement_mode(A3000 *a3000, AMA ama);
byte *program_counter_indirect_with_index_8bit_displacement_mode(A3000 *a3000, AMA ama);
byte *program_counter_indirect_with_index_base_displacement_mode(A3000 *a3000, AMA ama);
byte *program_counter_memory_indirect_postindexed_mode(A3000 *a3000, AMA ama);
byte *program_counter_memory_indirect_preindexed_mode(A3000 *a3000, AMA ama);
byte *absolute_short_addressing_mode(A3000 *a3000, AMA ama);
byte *absolute_long_addressing_mode(A3000 *a3000, AMA ama);
byte *immediate_data_mode(A3000 *a3000, AMA ama);


AMA get_AMA(A3000 *a3000);

byte *get_ea(A3000 *a3000, byte category);

#endif