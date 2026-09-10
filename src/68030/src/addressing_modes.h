#ifndef ADDRESSING_MODES_H
#define ADDRESSING_MODES_H


byte *data_register_direct_mode(a3000_t *a3000, ama_t ama);
byte *address_register_direct_mode(a3000_t *a3000, ama_t ama);
byte *address_register_indirect_mode(a3000_t *a3000, ama_t ama);
byte *address_register_indirect_with_postincrement_mode(a3000_t *a3000, ama_t ama);
byte *address_register_indirect_with_predecrement_mode(a3000_t *a3000, ama_t ama);
byte *address_register_indirect_with_displacement_mode(a3000_t *a3000, ama_t ama);
byte *address_register_indirect_with_index_8bit_mode(a3000_t *a3000, ama_t ama);
byte *address_register_indirect_with_index_base_displacement_mode(a3000_t *a3000, ama_t ama);
byte *memory_indirect_postindexed_mode(a3000_t *a3000, ama_t ama);
byte *memory_indirect_preindexed_mode(a3000_t *a3000, ama_t ama);
byte *program_counter_indirect_with_displacement_mode(a3000_t *a3000, ama_t ama);
byte *program_counter_indirect_with_index_8bit_displacement_mode(a3000_t *a3000, ama_t ama);
byte *program_counter_indirect_with_index_base_displacement_mode(a3000_t *a3000, ama_t ama);
byte *program_counter_memory_indirect_postindexed_mode(a3000_t *a3000, ama_t ama);
byte *program_counter_memory_indirect_preindexed_mode(a3000_t *a3000, ama_t ama);
byte *absolute_short_addressing_mode(a3000_t *a3000, ama_t ama);
byte *absolute_long_addressing_mode(a3000_t *a3000, ama_t ama);
byte *immediate_data_mode(a3000_t *a3000, ama_t ama);


ama_t get_AMA(a3000_t *a3000);

byte *get_ea(a3000_t *a3000, byte category);

#endif