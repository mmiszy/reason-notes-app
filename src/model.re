type incomplete_note = {mutable text: string};

type complete_note = {
  mutable text: string,
  id: string
};

let _notes: ref (list complete_note) = ref [];

let addNote (note: incomplete_note) :complete_note => {
  let id = string_of_int (List.length _notes.contents + 1);
  let newNote: complete_note = {id, text: note.text};
  _notes.contents = _notes.contents @ [newNote];
  newNote
};

let getNotes () :list complete_note => _notes.contents;

let deleteNote (id: string) :unit =>
  _notes.contents = List.filter (fun n => n.id !== id) _notes.contents;
