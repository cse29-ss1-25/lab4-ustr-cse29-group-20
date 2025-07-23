#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ustr.h"
#include "pset1.h"

/*
Initializes a new UStr with contents
*/
UStr new_ustr(char* contents) {
	int32_t bytes = strlen(contents);
	int32_t codepoints = utf8_strlen(contents);
	uint8_t all_ascii = bytes == codepoints;
	char* contents_copy = malloc(bytes + 1);
	strcpy(contents_copy, contents);
	UStr s = {
		codepoints,
		bytes,
		all_ascii,
		contents_copy
	};
	return s;
}

/*
Returns length of string
*/
int32_t len(UStr s) {
	return s.codepoints;
}

/*
Returns a substring of str, starting at index start (inclusive) 
and ending at index end (exclusive).

Returns an empty string on invalid range.
*/
UStr substring(UStr s, int32_t start, int32_t end) {
	// TODO: implement this
	char result[s.bytes];
	if (start >= end || start < 0 || end < 0 || end > s.codepoints) {
		
		return new_ustr("");
	}
	if (s.bytes == 0 || s.contents == NULL) {
		result[0] = '\0';
		return new_ustr(result);
	}

	if (s.is_ascii) {
		for(int i = start; i < end; i++) {
		       result[i-start] = s.contents[i];
		}
 		result[end-start] = '\0';
		return new_ustr(result);		
	} else {
  		  int32_t byte_start = 0;
  		  int32_t byte_end = 0;
  		  int32_t current_codepoint = 0;
  		  uint8_t* ptr = (uint8_t*)s.contents;
  		  
  		  // Find starting byte position
  		  while (current_codepoint < start && byte_start < s.bytes) {
  		      int size = utf8_codepoint_size(ptr[byte_start]);
  		      if (size == -1) {
  		          // Invalid UTF-8, skip this byte
  		          byte_start++;
  		          continue;
  		      }
  		      byte_start += size;
  		      current_codepoint++;
  		  }
  		  
  		  // Find ending byte position
  		  current_codepoint = start;
  		  byte_end = byte_start;
  		  while (current_codepoint < end && byte_end < s.bytes) {
  		      int size = utf8_codepoint_size(ptr[byte_end]);
  		      if (size == -1) {
  		          // Invalid UTF-8, skip this byte
  		          byte_end++;
  		          continue;
  		      }
  		      byte_end += size;
  		      current_codepoint++;
  		  }
		  int sub_bytes = byte_end - byte_start;
   		strncpy(result, s.contents + byte_start, sub_bytes);
		result[sub_bytes] = '\0';
		return new_ustr(result);
	}

}

/*
Given 2 strings s1 and s2, returns a string that is the result of 
concatenating s1 and s2. 
*/
UStr concat(UStr s1, UStr s2) {
	// TODO: implement this
	int total_bytes = s1.bytes + s2.bytes;
    char* new_contents = malloc(total_bytes + 1);  // +1 for null terminator


    // Copy s1 contents
    for (int i = 0; i < s1.bytes; i++) {
        new_contents[i] = s1.contents[i];
    }

    // Copy s2 contents
    for (int i = 0; i < s2.bytes; i++) {
        new_contents[i + s1.bytes] = s2.contents[i];
    }

    new_contents[total_bytes] = '\0';  // Null-terminate the new string

    UStr result;
    result.contents = new_contents;
    result.bytes = total_bytes;
    result.codepoints = s1.codepoints + s2.codepoints;
    result.is_ascii = s1.is_ascii && s2.is_ascii;

    return result;
}

/*
Given a string s and an index, return a string with the character at index 
removed from the original string. 

Returns the original string if index is out of bounds.
*/
UStr removeAt(UStr s, int32_t index) {
	// TODO: implement this

}

/*
Given a string s, return s reversed. 

Example: reverse("apples🍎 and bananas🍌") = "🍌sananab dna 🍎selppa")
*/
UStr reverse(UStr s) {
	// TODO: implement this
	char* result = malloc(s.bytes+1);
	if (s.is_ascii) {
		for(int i = 0; i < s.bytes; i++) {
			result[i] = s.contents[s.bytes-1-i];
		}
	} else {
		for(int i = 0; i < s.bytes; i++) {
			int size = utf8_codepoint_size(s.contents[s.bytes-1-i]);
			if (size != 1 && size != -1) {
				for(int j = 0; j < size; j++) {
					result[i-size+1 + j] = s.contents[s.bytes-1-i+j];
				}
				
			} else if (size == 1){
				result[i] = s.contents[s.bytes-1-i];
			}
		}

	}
	result[s.bytes] = '\0';
	UStr reverse = new_ustr(result);
	free(result);
	return reverse;
}


void print_ustr(UStr s) {
	printf("%s [codepoints: %d | bytes: %d]", s.contents, s.codepoints, s.bytes);
}

void free_ustr(UStr s) {
	if (s.contents != NULL) {
		free(s.contents);
		s.contents = NULL;
	}
}

