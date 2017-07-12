type incomplete_note = {mutable text: string};

type complete_note = {
  mutable text: string,
  id: string
};

let _notes: ref (list complete_note) = ref [];

let noteFromJson json :complete_note =>
  Json.Decode.{id: json |> field "id" string, text: json |> field "text" string};

let notesFromJson json :list complete_note => json |> Json.Decode.list noteFromJson;

let loadedNotes =
  switch (Dom.Storage.localStorage |> Dom.Storage.getItem "notes") {
  | None => []
  | Some notes => notes |> Js.Json.parseExn |> notesFromJson
  };

_notes.contents = (
  if (List.length loadedNotes > 0) {
    loadedNotes
  } else {
    [{id: "1", text: ""}]
  }
);

let saveNotes () :unit => {
  let notesJson =
    _notes.contents |> Array.of_list |>
    Array.map (
      fun {id, text} => Js.Dict.fromList [("text", Js.Json.string text), ("id", Js.Json.string id)]
    ) |> Js.Json.objectArray |> Js.Json.stringify;
  Dom.Storage.localStorage |> Dom.Storage.setItem "notes" notesJson
};

let addNote (note: incomplete_note) :complete_note => {
  let id = string_of_int (List.length _notes.contents + 1);
  let newNote: complete_note = {id, text: note.text};
  _notes.contents = _notes.contents @ [newNote];
  saveNotes ();
  newNote
};

let updateNote (note: complete_note) :complete_note => {
  _notes.contents =
    List.map
      (
        fun n =>
          if (n.id == note.id) {
            note
          } else {
            n
          }
      )
      _notes.contents;
  saveNotes ();
  note
};

let getNotes () :list complete_note => _notes.contents;

let deleteNote (id: string) :unit => {
  _notes.contents = List.filter (fun n => n.id !== id) _notes.contents;
  saveNotes ();
  ()
};
