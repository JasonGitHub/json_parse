// Created by Jason
// Dec 4, 2014

#include <stdbool.h>
#include <jansson.h>

bool read_input_schema(json_t *root) {
  json_t *input = json_object_get(root, "input");
  // input must be an array of relations, even if there is only one
  if (!json_is_array(input)) {
    fprintf(stderr, "error: input is not an array of relations\n");
    json_decref(root);
    return false;
  }
  int i, j;
  // read each relation in input
  for (i = 0; i < json_array_size(input); ++i) {
    json_t *relation, *name, *data, *columns, *create_hash;
    const char *name_text; 
    relation = json_array_get(input, i);
    // a relation must be an object
    if (!json_is_object(relation)) {
      fprintf(stderr, "error: relation %d is not an object\n", i);
      json_decref(root);
      return false;
    }
    // read attributes in relation
    name = json_object_get(relation, "name");
    if (!json_is_string(name)) {
      fprintf(stderr, "error: name of relation %d is not a string\n", i);
      json_decref(root);
      return false;
    }
    name_text = json_string_value(name);
    //FIXME: Optest value assignment plugin here
    printf("relation name: %s\n", name_text);

    data = json_object_get(relation, "data");
    if (!json_is_array(data)) {
      fprintf(stderr, "error: data of relation %d is not an array\n", i);
      json_decref(root);
      return false;
    }
    for (j = 0; j < json_array_size(data); ++j) {
      json_t *data_part;
      data_part = json_array_get(data, j);
      if (!json_is_string(data_part)) {
        fprintf(stderr, "error: name of part %d is not a string\n", i);
        json_decref(root);
        return false;
      }
      const char *data_part_text = json_string_value(data_part);
      //FIXME: Optest value assignment plugin here
      printf("input file name: %s\n", data_part_text); 
    }

    columns = json_object_get(relation, "columns");
    if (!json_is_array(columns)) {
      fprintf(stderr, "error: columns of relation %d is not an array\n", i);
      json_decref(root);
      return false;
    }
    const char *key;
    json_t *value;
    for (j = 0; j < json_array_size(columns); ++j) {
      json_t *one_column;
      one_column = json_array_get(columns, j);
      json_object_foreach(one_column, key, value) {
        if (!json_is_string(value)) {
          fprintf(stderr, "error: name of column %d is not a string\n", i);
          json_decref(root);
          return false;
        }
        const char *value_text = json_string_value(value);
        //FIXME: Optest value assignment plugin here
        printf("%s : %s\n", key, value_text); 
      }
    }

    create_hash = json_object_get(create_hash, "create_hash");
    //TODO: parse create_hash
  }
  return true;
}

bool read_output_schema(json_t *root) {
  json_t *output = json_object_get(root, "output");
  // output must be an array of relations, even if there is only one
  if (!json_is_array(output)) {
    fprintf(stderr, "error: output is not an array of relations\n");
    json_decref(root);
    return false;
  }
  int i, j;
  // read each relation in output
  for (i = 0; i < json_array_size(output); ++i) {
    json_t *relation, *name, *data, *num_rows, *columns, *create_hash;
    const char *name_text; 
    relation = json_array_get(output, i);
    // a relation must be an object
    if (!json_is_object(relation)) {
      fprintf(stderr, "error: relation %d is not an object\n", i);
      json_decref(root);
      return false;
    }
    // read attributes in relation
    name = json_object_get(relation, "name");
    if (!json_is_string(name)) {
      fprintf(stderr, "error: name of relation %d is not a string\n", i);
      json_decref(root);
      return false;
    }
    name_text = json_string_value(name);
    //FIXME: Optest value assignment plugin here
    printf("relation name: %s\n", name_text);

    data = json_object_get(relation, "data");
    if (!json_is_array(data)) {
      fprintf(stderr, "error: data of relation %d is not an array\n", i);
      json_decref(root);
      return false;
    }
    for (j = 0; j < json_array_size(data); ++j) {
      json_t *data_part;
      data_part = json_array_get(data, j);
      if (!json_is_string(data_part)) {
        fprintf(stderr, "error: name of part %d is not a string\n", i);
        json_decref(root);
        return false;
      }
      const char *data_part_text = json_string_value(data_part);
      //FIXME: Optest value assignment plugin here
      printf("input file name: %s\n", data_part_text); 
    }

    // check if num_rows is set
    // if yes, it is buffered; otherwise it's streamed
    num_rows = json_object_get(relation, "num_rows");
    if (num_rows != NULL) {
      if (!json_is_integer(num_rows)) {
        fprintf(stderr, "error: num_rows of relation %d is not an integer\n", i);
        json_decref(root);
        return false;
      }
      int num_rows_val = json_integer_value(num_rows);
      printf("num_rows: %d\n", num_rows_val);
    }

    columns = json_object_get(relation, "columns");
    if (!json_is_array(columns)) {
      fprintf(stderr, "error: columns of relation %d is not an array\n", i);
      json_decref(root);
      return false;
    }
    const char *key;
    json_t *value;
    for (j = 0; j < json_array_size(columns); ++j) {
      json_t *one_column;
      one_column = json_array_get(columns, j);
      json_object_foreach(one_column, key, value) {
        if (!json_is_string(value)) {
          fprintf(stderr, "error: name of column %d is not a string\n", i);
          json_decref(root);
          return false;
        }
        const char *value_text = json_string_value(value);
        //FIXME: Optest value assignment plugin here
        printf("%s : %s\n", key, value_text); 
      }
    }
  }
  return true;
}

bool read_schema(const char *json_file_name) {
  json_t *root;
  json_error_t error;
  root = json_load_file(json_file_name, 0, &error);
  // check if read successed
  if (!root) {
    fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
    return false;
  }
  // check if root is an object
  if (!json_is_object(root)) {
    fprintf(stderr, "error: root is not an object\n");
    json_decref(root);
    return false;
  }
  // fetch "input" & "output"
  return read_input_schema(root) && read_output_schema(root);
}

int main() {
  if (read_schema("io.json") != 0) {
    printf("Successfully read json configuration file\n");
  }
  return 0;
}
